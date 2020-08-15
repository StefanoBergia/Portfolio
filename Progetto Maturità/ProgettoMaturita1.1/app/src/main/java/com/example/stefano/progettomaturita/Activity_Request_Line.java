package com.example.stefano.progettomaturita;

import android.content.Intent;
import android.content.pm.PackageManager;
import android.content.pm.ResolveInfo;
import android.os.Bundle;
import android.support.design.widget.FloatingActionButton;
import android.support.design.widget.Snackbar;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.Toolbar;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.EditText;

import java.util.List;

public class Activity_Request_Line extends AppCompatActivity {

        EditText editDeparture = null;
        EditText editArrival = null;
        EditText editDitta = null;

        FloatingActionButton fab;

        @Override
        protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_request_line);
        Toolbar toolbar = (Toolbar) findViewById(R.id.toolbar);
        setSupportActionBar(toolbar);

        FloatingActionButton fab = (FloatingActionButton) findViewById(R.id.fab);
        fab.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                //nel momento che viene fatto click sul FloatingActionButton viene avviata la funzione che invia la mail
                btnInviaMail_onClick(view);
            }
        });
        getSupportActionBar().setDisplayHomeAsUpEnabled(true);

        editDeparture = (EditText)findViewById(R.id.richiediDepartureTxt);
        editArrival = (EditText)findViewById(R.id.richiediArrivalTxt);
        editDitta = (EditText)findViewById(R.id.richiediDittaTrasporti);

    }

    public void btnInviaMail_onClick(View v)
    {
        //controllo che i campi richiesti siano compilati
        if(!editDeparture.getText().toString().equals("") && !editArrival.getText().toString().equals("") && !editDitta.getText().toString().equals("")) {

            //genero il testo della mail
            String body = "PARTENZA: " + editDeparture.getText().toString() +
                    "\nARRIVO: " + editArrival.getText().toString() +
                    "\nDITTA: " + editDitta.getText().toString();

            try {

                //genero la mail e apro il client gmail per poterla inviare

                Intent emailIntent = new Intent(Intent.ACTION_SEND);
                emailIntent.putExtra(Intent.EXTRA_EMAIL, new String[]{getString(R.string.admin_email)});
                emailIntent.putExtra(Intent.EXTRA_SUBJECT, "Richiesta nuova linea");
                emailIntent.setType("text/plain");
                emailIntent.putExtra(android.content.Intent.EXTRA_TEXT, body);

                final PackageManager pm = this.getPackageManager();
                final List<ResolveInfo> matches = pm.queryIntentActivities(emailIntent, 0);
                ResolveInfo best = null;
                for (final ResolveInfo info : matches)
                    if (info.activityInfo.packageName.endsWith(".gm") || info.activityInfo.name.toLowerCase().contains("gmail"))
                        best = info;

                if (best != null)
                    emailIntent.setClassName(best.activityInfo.packageName, best.activityInfo.name);
                startActivity(emailIntent);

            }catch(Exception ex)
            {
                Snackbar snack = Snackbar.make(v, ex.getMessage().toString(), Snackbar.LENGTH_LONG);
                snack.show();
            }
        }
        else
        {
            Snackbar snack = Snackbar.make(v, getString(R.string.fill_msg), Snackbar.LENGTH_SHORT);
            snack.show();
        }
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        getMenuInflater().inflate(R.menu.guide_about, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        Static_Shared_Menu.OptionItemSelected(item,this,getString(R.string.request_guide));
        return super.onOptionsItemSelected(item);
    }
}