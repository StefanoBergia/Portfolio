package com.example.stefano.progettomaturita;


import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.support.design.widget.FloatingActionButton;
import android.support.design.widget.Snackbar;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.CardView;
import android.support.v7.widget.RecyclerView;
import android.support.v7.widget.Toolbar;
import android.view.ContextMenu;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.TextView;
import java.util.ArrayList;
import java.util.Vector;

public class Activity_Detail extends AppCompatActivity {

    //elementi del layout
    private TextView nomeLinea;
    private TextView nomeDitta;
    private TextView autista;
    private  TextView autobus;
    private  TextView ritardoTxt;
    private CardView cvAvviso;
    private RecyclerView rv;

    //idOrario della linea corrente
    private  String idOrario;

    //array contente tutte le informazioni sulle fermate della linea
    private Vector<Fermata> fermate;

    //View della fermata su cui è stato fatto click
    private Adapter_Fermata.FermataViewHolder currentFermataView=null;

    //Id della fermata su cui è stato fatto click
    private String currentFermata=null;

    //dati della linea da salvare su file
    private String currentData;

    private String JsonFermate;

    //recupero il contesto per utilizzi successivi
    private Context cx;

    //parametri passati dall'intent
    private Bundle args;

    //variabile di supporto utilizzare per determinare lo stato del pulsante slava/elimina
    private boolean add;

    //nomi dei file utilizzati
    private String filePreferiti;
    private String fileNotifiche;

    private String regid;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_detail);
        Toolbar toolbar = (Toolbar) findViewById(R.id.toolbar);
        setSupportActionBar(toolbar);

        //recupero il contesto per utilizzi successivi
        cx=this;

        //recupero gli elementi del layout
        nomeLinea = (TextView) findViewById(R.id.nomeLinea);
        nomeDitta = (TextView) findViewById(R.id.nomeDitta);
        rv = (RecyclerView) findViewById(R.id.rvFermate);
        cvAvviso = (CardView) findViewById(R.id.divIncorso);

        //recupero gli elemnti del layout interni alla cardView
        autista = (TextView) cvAvviso.findViewById(R.id.autista);
        autobus = (TextView) cvAvviso.findViewById(R.id.autobus);
        ritardoTxt = (TextView) cvAvviso.findViewById(R.id.ritardoTxt);


        //recupero il nome dei file
        filePreferiti=this.getFilesDir()+"/"+getString(R.string.saved);
        fileNotifiche =this.getFilesDir()+"/"+getString(R.string.saved_n);

        //recupero i parametri dell'Intent
        Intent intent=getIntent();
        args = intent.getExtras();

        //visualizzo le informazioni nel layout
        nomeLinea.setText(String.format("Linea: %s", args.getString("NomeLinea")));
        nomeDitta.setText(String.format("Ditta: %s", args.getString("Ditta")));

        //recupero l'idOrario, utilizzato per recuperare le fermate dal server
        idOrario = args.getString("IDOrario");

        //recupero il RegID
        regid= Static_Shared_Preferences.GetString(this,"REGID");

        //verifico se la linea corrente è in corso
        ReloadInCorso();

        //serializzo in CSV le informazioni riguardanti la linea corrente
        currentData=idOrario + ";"+args.getString("Ditta")+";"+args.getString("IDLinea")+";"+args.getString("Ora")+";"+args.getString("NomeLinea");
        JsonFermate="";
        //recupero le fermate che costituiscono la linea
        Dictionary data=new Dictionary();
        data.AddItem("IDOrario",idOrario);
        new Async_Get_Fermate(getString(R.string.get_fermate),data,this,rv,fileNotifiche,filePreferiti,currentData).execute();


        //registro l'evento click sul floatingActionButton
        FloatingActionButton fab = (FloatingActionButton) findViewById(R.id.map);
        fab.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {

                if(Static_Connection_Checker.Check(cx)) {
                    if (fermate != null && fermate.size() > 0) {

                        //creo l'intent per avviare la map activity
                        Intent intent = new Intent(Activity_Detail.this, Activity_Map.class);

                        //passo a tutti gli argomenti correnti
                        intent.putExtras(args);

                        //passo alla map activity anche tutte le informazioni relative alle fermate
                        //in particolare le coordinate geografiche
                        ArrayList<String> argsFermate = new ArrayList<String>();

                        for (int i = 0; i < fermate.size(); i++)
                            argsFermate.add(fermate.get(i).Serialize());

                        intent.putStringArrayListExtra("Fermate", argsFermate);

                        startActivity(intent);
                    }
                }else
                    Snackbar.make(((Activity_Detail)cx).findViewById(R.id.rel), getString(R.string.no_internet_2), Snackbar.LENGTH_LONG)
                            .setAction("Action", null).show();
            }
        });

        getSupportActionBar().setDisplayHomeAsUpEnabled(true);
    }


    public void AppendFermate(String json)
    {
        JsonFermate=";"+json;
    }

    //metodo che verifica se la linea corrente è in corso e visualizza un diquadro di avviso nel caso che ciò avvenga
    public void ReloadInCorso() {
        Dictionary data =new Dictionary();
        data.AddItem("IDOrario",idOrario);
        new Async_Get_In_Corso(getString(R.string.get_in_corso),data,cvAvviso, autista, autobus, ritardoTxt).execute();
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        getMenuInflater().inflate(R.menu.detail_menu, menu);

        //verifico se la linea è già salvata per determinare lo stato del pulsante slava/elimina
        if(Static_Gestione_File.Contains(filePreferiti,currentData)){
            add = false;
            menu.findItem(R.id.action_save).setIcon(getResources().getDrawable(R.drawable.ic_remove_white_24dp));
        }
        else {
            add = true;
            menu.findItem(R.id.action_save).setIcon(getResources().getDrawable(R.drawable.ic_add_white_24dp));
        }
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {


        switch (item.getItemId())
        {
            case R.id.action_reload:
                ReloadInCorso();
                break;
            case R.id.action_save:
                String msg="";

                //verifico che sia presente la connessione

                if(Static_Connection_Checker.Check(this)) {
                    //verifico se la linea è già salvata per determinare lo stato del pulsante slava/elimina
                    if (add == true) {
                        try {
                            //se la linea non è ancora presente nel file dei preferiti la aggiungo
                            Static_Gestione_File.AppendToFile(filePreferiti, currentData+JsonFermate);
                            msg = getString(R.string.line_saved);
                            add = false;
                            //modifico l'icona del pulsante
                            item.setIcon(getResources().getDrawable(R.drawable.ic_remove_white_24dp));

                            //////////////SALVATAGGIO SU SQLLITE///////////////
                            ///FERMATE
                            //POLYLINE
                        } catch (Exception e) {
                            //se si verifica un errore annullo tutte le operazioni
                            msg = getString(R.string.line_save_error);
                            item.setIcon(getResources().getDrawable(R.drawable.ic_add_white_24dp));
                            add = true;
                        }

                    } else {
                        try {
                            //rimuovo la linea dal file dei preferiti
                            Static_Gestione_File.RemoveFromFile(filePreferiti, currentData);
                            msg = getString(R.string.line_removed);
                            add = true;
                            //modifico l'icona del pulsante
                            item.setIcon(getResources().getDrawable(R.drawable.ic_add_white_24dp));

                            //////////////RIMOZIONE DA SQLLITE///////////////

                        } catch (Exception e) {
                            //se si verifica un errore annullo tutte le operazioni
                            msg = getString(R.string.line_remove_error);
                            item.setIcon(getResources().getDrawable(R.drawable.ic_remove_white_24dp));
                            add = false;
                        }
                    }

                    //mostro un messaggio all'utente per informarlo del risultato dell'operazione
                    Snackbar.make(this.findViewById(R.id.rel), msg, Snackbar.LENGTH_LONG)
                            .setAction("Action", null).show();
                }else
                    Snackbar.make(this.findViewById(R.id.rel), getString(R.string.no_internet_2), Snackbar.LENGTH_LONG)
                            .setAction("Action", null).show();

                break;
            case android.R.id.home:
                //torna all'activity precedente
                goBack();
                break;
            default:
                Static_Shared_Menu.OptionItemSelected(item,this,getString(R.string.detail_guide));
        }

        return super.onOptionsItemSelected(item);
    }


    @Override
    public void onBackPressed() {
        super.onBackPressed();
        goBack();
    }

    //avvia una activity in base al valore del parametro "Back"
    public void goBack() {
        int prec=args.getInt("Back");
        if(!Static_Connection_Checker.Check(this))
            prec=1;
        Intent intent=new Intent(Activity_Detail.this,Activity_Main.class);
        switch (prec)
        {
            case 2:
                intent=new Intent(Activity_Detail.this,Activity_Search.class);
                break;
            case 3:
                intent=new Intent(Activity_Detail.this,Activity_Gestione_Notifiche.class);
                break;
        }
        startActivity(intent);
    }


    /////////Context menu////////
    @Override
    public void onCreateContextMenu(ContextMenu menu, View v,ContextMenu.ContextMenuInfo menuInfo) {
        super.onCreateContextMenu(menu, v, menuInfo);

        //aggiungo le voci per le notifiche
        menu.setHeaderTitle(getString(R.string.cxmenu_header));
        menu.add(0, 5, 0, getString(R.string.five_min));
        menu.add(0, 10, 0, getString(R.string.ten_min));
        menu.add(0, 15, 0, getString(R.string.fifteen_min));

        //recupero le notifiche registrate
        Vector<String> saved = Static_Gestione_File.GetSaved(fileNotifiche);
        for (int j = 0; j < saved.size(); j++) {
            //se la notifica è registrata, allora rimuovo tutte le voci e ne aggiungo una per poter rimuovere la notifica stessa
            if (saved.get(j).startsWith(getIdOrario() + ";" + currentFermata)) {
                menu.clear();
                menu.add(0, 9999, 0, getString(R.string.remove_notification));
                break;
            }
        }
    }

    @Override
    public boolean onContextItemSelected(MenuItem item) {

        String path="";

        //genero i dati da inviare
        Dictionary data =new Dictionary();
        data.AddItem("RegID",regid);
        data.AddItem("IDOrario",idOrario);
        data.AddItem("IDFermata",currentFermata);

        switch (item.getItemId()){
            case 5:
            case 10:
            case 15:
                //imposto il percorso della risorsa corretto e aggiungo il parametro del tempo
                path=getString(R.string.web_add_notification);
                data.AddItem("Tempo",item.getItemId()+"");
                break;
            case 9999:
                ////imposto il percorso della risorsa corretto
                path=getString(R.string.web_remove_notification);
                break;
        }

        //invio la richiesta e gestisco la risposta
        new Async_Register_Delete_Notifications(path,data,this,fileNotifiche).execute();
        return true;
    }


    public void setFermate(Vector<Fermata> frm){this.fermate=frm;}

    public Vector<Fermata> getFermate(){return this.fermate;}

    public void setCurrentFermata(String IDfermata){this.currentFermata=IDfermata;}

    public void setCurrentFermataView(Adapter_Fermata.FermataViewHolder v){currentFermataView=v;}

    public Adapter_Fermata.FermataViewHolder getCurrentFermataView(){return  currentFermataView;}

    public  String getIdOrario() {return idOrario;}

}
