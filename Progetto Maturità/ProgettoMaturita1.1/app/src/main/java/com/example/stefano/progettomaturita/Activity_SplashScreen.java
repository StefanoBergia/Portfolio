package com.example.stefano.progettomaturita;

import android.content.Intent;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;

/**
 * Created by stefano on 07/04/16.
 */
public class Activity_SplashScreen extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        try {
            //attendo un secondo per fare vedere il logo
            Thread.sleep(1000);
        }catch(Exception ex){
        }

        //creo i file utilizzati dall'app
        Static_Gestione_File.CreateFile(this.getFilesDir()+"/"+getString(R.string.saved));
        Static_Gestione_File.CreateFile(this.getFilesDir()+"/"+getString(R.string.saved_n));

        //faccio richiesta al server per il register ID
        new Async_Register(this,getString(R.string.project_number)).execute();
    }

    public void StartMain(String regid){
        //inserisco il register_id nelle sharedpreferences
        Static_Shared_Preferences.PutString(this,"REGID",regid);
        //avvio l'activity main
        Intent intent = new Intent(this, Activity_Main.class);
        startActivity(intent);
        finish();
    }
}