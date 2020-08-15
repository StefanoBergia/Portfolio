package com.example.stefano.progettomaturita;

import android.app.AlertDialog;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.pm.PackageInfo;
import android.content.pm.PackageManager;
import android.os.Bundle;
import android.support.design.widget.FloatingActionButton;
import android.support.design.widget.Snackbar;
import android.support.v7.widget.LinearLayoutManager;
import android.support.v7.widget.RecyclerView;
import android.text.Html;
import android.view.View;
import android.support.design.widget.NavigationView;
import android.support.v4.view.GravityCompat;
import android.support.v4.widget.DrawerLayout;
import android.support.v7.app.ActionBarDrawerToggle;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.Toolbar;
import android.view.Menu;
import android.view.MenuItem;
import android.widget.TextView;
import android.widget.Toast;
import java.util.Vector;

public class Activity_Main extends AppCompatActivity
        implements NavigationView.OnNavigationItemSelectedListener,Interface_Open_Detail {

    //nome del file delle linee salvate
    private String filename;

    //vettore contente le informazioni visualizzate nelle cardview
    private Vector<Support_Card_Linea> linee;

    //registre_id recuperato nella splashScreen
    private String regid;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        Toolbar toolbar = (Toolbar) findViewById(R.id.toolbar);
        setSupportActionBar(toolbar);

        DrawerLayout drawer = (DrawerLayout) findViewById(R.id.drawer_layout);
        ActionBarDrawerToggle toggle = new ActionBarDrawerToggle(
                this, drawer, toolbar, R.string.navigation_drawer_open, R.string.navigation_drawer_close);
        drawer.setDrawerListener(toggle);
        toggle.syncState();


        NavigationView navigationView = (NavigationView) findViewById(R.id.nav_view);
        navigationView.setNavigationItemSelectedListener(this);


        /***********************************/

        //recupero il regid
        this.regid= Static_Shared_Preferences.GetString(this,"REGID");
        final Context cx=this;

        FloatingActionButton fab = (FloatingActionButton) findViewById(R.id.fab);
        fab.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                if(Static_Connection_Checker.Check(cx)){
                //avvio la Activity_Search
                Intent intent = new Intent(Activity_Main.this,Activity_Search.class);
                startActivity(intent);
                }else
                {
                    //informo l'utenet del fatto che è offline
                    Snackbar snack = Snackbar.make(((Activity_Main)cx).findViewById(android.R.id.content), getString(R.string.no_internet), Snackbar.LENGTH_LONG);
                    snack.show();

                }

            }
        });



        //recupero la RecyclerView e la textview
        RecyclerView rv=(RecyclerView)findViewById(R.id.rv);
        TextView label=(TextView)findViewById(R.id.label);

        //recupero le linee salvate
        filename=this.getFilesDir()+"/"+getString(R.string.saved);
        Vector<String> saved= Static_Gestione_File.GetSaved(filename);

        if(saved.size()>0){

            label.setText(getString(R.string.label_seguite));
            label.setTextSize(18);
            label.setGravity(0);

            //carico il vettore in base al contenuto del file
            linee = new Vector<Support_Card_Linea>();
            Support_Card_Linea supp = null;
            for (int i = 0; i < saved.size(); i++) {
                supp = new Support_Card_Linea();
                supp.DeSerialize(saved.get(i), this);
                linee.add(supp);
            }

            //genero le cardview attraverso la classe Adpater_Linee
            LinearLayoutManager llm = new LinearLayoutManager(this);
            rv.setLayoutManager(llm);
            Adpater_Linee adapter = new Adpater_Linee(linee,this);
            rv.setAdapter(adapter);
        }

        Static_Shared_Preferences.PutString(this,"FILE_UPDATED","");

        //verifico lo stato della connessione
        if(Static_Connection_Checker.Check(this))
        {
            //se la connessione è attiva, recupero le notifiche a cui sono registrato dal server
            Dictionary data=new Dictionary();
            data.AddItem("RegID",regid);
            new Async_Get_File_Registrazioni(getString(R.string.get_notifiche),data,this).execute();

            //memorizzo il fatto che il file delle notifiche è aggiornato
            Static_Shared_Preferences.PutString(this,"FILE_UPDATED","OK");
        }else
        {
            //informo l'utenet del fatto che è offline
            Snackbar snack = Snackbar.make(this.findViewById(android.R.id.content), getString(R.string.no_internet), Snackbar.LENGTH_LONG);
            snack.show();

            Static_Shared_Preferences.PutString(this,"FILE_UPDATED","KO");

        }

    }

    @Override
    public void onBackPressed() {
        DrawerLayout drawer = (DrawerLayout) findViewById(R.id.drawer_layout);
        if (drawer.isDrawerOpen(GravityCompat.START)) {
            drawer.closeDrawer(GravityCompat.START);
        } else {
            this.finish();
        }
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        getMenuInflater().inflate(R.menu.main, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        //gestione del menu generico
        int id = item.getItemId();
        Static_Shared_Menu.OptionItemSelected(item,this,getString(R.string.main_guide_msg));
        return super.onOptionsItemSelected(item);
    }

    @SuppressWarnings("StatementWithEmptyBody")
    @Override
    public boolean onNavigationItemSelected(MenuItem item) {

        // gestione della navbar laterale

        switch(item.getItemId())
        {
            case R.id.nav_search:
                if(Static_Connection_Checker.Check(this)) {
                    Intent intent = new Intent(Activity_Main.this, Activity_Search.class);
                    startActivity(intent);
                } else
                {
                    Snackbar snack = Snackbar.make(this.findViewById(android.R.id.content), getString(R.string.no_internet_2), Snackbar.LENGTH_LONG);
                    snack.show();
                }
                break;

            case R.id.nav_about:
                new AlertDialog.Builder(this)
                    .setTitle(getString(R.string.app_name))
                    .setMessage(Html.fromHtml(getString(R.string.about)))
                    .setPositiveButton(android.R.string.ok, new DialogInterface.OnClickListener() {
                        public void onClick(DialogInterface dialog, int which) {
                        }
                    })
                    .setIcon(R.drawable.nautibus_icon_192)
                    .show();
                break;

            case R.id.nav_track:
                if(Static_Connection_Checker.Check(this)) {
                //apre l'activity per la richiesta di una nuova linea
                Intent trIntent=new Intent(this,Activity_Request_Line.class);
                startActivity(trIntent);
                } else
                {
                    Snackbar snack = Snackbar.make(this.findViewById(android.R.id.content), getString(R.string.no_internet_2), Snackbar.LENGTH_LONG);
                    snack.show();
                }
                break;
            case R.id.nav_share:
                //condivisione dell0app tramite whatsapp
                PackageManager pm=getPackageManager();
                try {

                    Intent waIntent = new Intent(Intent.ACTION_SEND);
                    waIntent.setType("text/plain");
                    String text = getString(R.string.whatsapp_msg);

                    PackageInfo info=pm.getPackageInfo("com.whatsapp", PackageManager.GET_META_DATA);
                    waIntent.setPackage("com.whatsapp");

                    waIntent.putExtra(Intent.EXTRA_TEXT, text);
                    startActivity(waIntent);

                } catch (PackageManager.NameNotFoundException e) {
                    Snackbar snack = Snackbar.make(this.findViewById(android.R.id.content), getString(R.string.no_whatsapp), Snackbar.LENGTH_LONG);
                    snack.show();
                }
                break;
            case R.id.nav_notification:
                if(Static_Connection_Checker.Check(this)) {
                    //avvia l'activity per la gestione delle notifiche
                    Intent gestNotifiche = new Intent(this, Activity_Gestione_Notifiche.class);
                    startActivity(gestNotifiche);
                } else
                {
                    Snackbar snack = Snackbar.make(this.findViewById(android.R.id.content), getString(R.string.no_internet_2), Snackbar.LENGTH_LONG);
                    snack.show();
                }
                break;
        }

        //gestione animazione
        try {
            DrawerLayout drawer = (DrawerLayout) findViewById(R.id.drawer_layout);
            drawer.closeDrawer(GravityCompat.START);
        }catch(Exception ex)
        {
            Toast.makeText(this, ex.getMessage(), Toast.LENGTH_LONG).show();
        }
        DrawerLayout drawer = (DrawerLayout) findViewById(R.id.drawer_layout);
        drawer.closeDrawer(GravityCompat.START);

        return true;
    }

    //avvia l'activity dettaglio per una delle linee rappresentate dalle cardview
    public void OpenDetail(Support_Card_Linea Linea){
        Intent intent = new Intent(Activity_Main.this,Activity_Detail.class);
        intent.putExtra("IDOrario",Linea.getIDOrario());
        intent.putExtra("Ditta",Linea.getDitta());
        intent.putExtra("IDLinea",Linea.getIDLinea());
        intent.putExtra("Ora",Linea.getOra());
        intent.putExtra("NomeLinea",Linea.getNomeLinea());

        //indica che la detailactivity è stata lanciata dalla main Activity
        intent.putExtra("Back",1);

        startActivity(intent);
    }
}
