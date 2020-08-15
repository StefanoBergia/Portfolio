package com.example.stefano.progettomaturita;

import android.content.Intent;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.LinearLayoutManager;
import android.support.v7.widget.RecyclerView;
import android.support.v7.widget.Toolbar;
import android.view.ContextMenu;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.TextView;
import java.util.Vector;

public class Activity_Gestione_Notifiche extends AppCompatActivity implements Interface_Open_Detail {

    private String RegID = null;
    private String IdOrario = null;
    private String Fermata = null;
    private String AnticipoNotifica = null;
    private RecyclerView rv;

    private String fileNotifiche;

    Vector<String> datiLinea;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_gestione_notifiche);
        Toolbar toolbar = (Toolbar) findViewById(R.id.toolbar);
        setSupportActionBar(toolbar);
        getSupportActionBar().setDisplayHomeAsUpEnabled(true);

        //recupero e inizializzo la recyclerview
        rv = (RecyclerView)findViewById(R.id.recycler) ;
        LinearLayoutManager llm = new LinearLayoutManager(this);
        rv.setLayoutManager(llm);

        //recupero l'url dl file delle notifiche
        fileNotifiche =this.getFilesDir()+"/"+getString(R.string.saved_n);

        datiLinea = new Vector<String>();

        //recupero dal server i dati relativi alle notifiche registrate
        RegID= Static_Shared_Preferences.GetString(this,"REGID");
        Dictionary data= new Dictionary();
        data.AddItem("RegistrationID",RegID);
        new Async_Get_Iscrizioni(getString(R.string.get_iscrizioni),data, this,rv, (TextView)findViewById(R.id.lblHeadNotifiche)).execute();
    }


    //metodo per aprire la Activity_Detail
    public void OpenDetail(Support_Card_Linea iscrizione){
        Intent intent = new Intent(Activity_Gestione_Notifiche.this,Activity_Detail.class);
        intent.putExtra("IDLinea", iscrizione.getIDLinea());
        intent.putExtra("NomeLinea", iscrizione.getNomeLinea());
        intent.putExtra("Ditta", ((Support_Card_Gestione_Iscrizioni)iscrizione).getRagSoc());
        intent.putExtra("IDOrario", iscrizione.getIDOrario());
        intent.putExtra("Ora",((Support_Card_Gestione_Iscrizioni) iscrizione).getOrario());
        intent.putExtra("Back",3);

        startActivity(intent);
    }

    @Override
    public void onCreateContextMenu(ContextMenu menu, View v, ContextMenu.ContextMenuInfo menuInfo) {

        super.onCreateContextMenu(menu, v, menuInfo);
        Vector<String> saved = Static_Gestione_File.GetSaved(fileNotifiche);

        menu.setHeaderTitle("Notifica quando mancano");

        if(AnticipoNotifica.equals("5")) {
            menu.add(0, 10, 0, "10 minuti");
            menu.add(0, 15, 0, "15 minuti");
            menu.add(0, 9999, 0, "Rimuovi notifica");
        }
        if(AnticipoNotifica.equals("10"))
        {
            menu.add(0, 5, 0, "5 minuti");
            menu.add(0, 15, 0, "15 minuti");
            menu.add(0, 9999, 0, "Rimuovi notifica");
        }
        if(AnticipoNotifica.equals("15"))
        {
            menu.add(0, 5, 0, "5 minuti");
            menu.add(0, 10, 0, "10 minuti");
            menu.add(0, 9999, 0, "Rimuovi notifica");
        }
    }

    @Override
    public boolean onContextItemSelected(MenuItem item) {
        String path;
        Dictionary data=new Dictionary();
        data.AddItem("RegID",RegID);
        data.AddItem("IDOrario",IdOrario);
        data.AddItem("IDFermata",Fermata);

        switch (item.getItemId()){
            case 5:
            case 10:
            case 15:
                data.AddItem("Tempo",item.getItemId()+"");
                new Async_Update_Notification(getString(R.string.update_notification),data,this,fileNotifiche).execute();
                break;
            case 9999:
                new Async_Update_Notification(getString(R.string.web_remove_notification),data,this,fileNotifiche).execute();
                break;

        }
        return true;
    }

    //metodo utilizzato dall'adapteer della recyclerview per passare i dati all'activity
    public void setParametri(String IDOrario, String IDFermata, String orario)
    {
        this.IdOrario = IDOrario;
        this.Fermata = IDFermata;
        this.AnticipoNotifica = orario;
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        getMenuInflater().inflate(R.menu.guide_about, menu);
        return true;
    }

    @Override
    public void onBackPressed() {
        super.onBackPressed();
        Intent intent= new Intent(Activity_Gestione_Notifiche.this,Activity_Main.class);
        startActivity(intent);
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {

        switch(item.getItemId())
        {
            case R.id.home:
                Intent intent= new Intent(Activity_Gestione_Notifiche.this,Activity_Main.class);
                startActivity(intent);
                break;
            default:
                Static_Shared_Menu.OptionItemSelected(item,this,getString(R.string.gestione_guida));
        }
        return super.onOptionsItemSelected(item);

    }
}
