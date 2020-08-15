package com.example.stefano.progettomaturita;

import android.os.AsyncTask;
import com.google.android.gms.gcm.GoogleCloudMessaging;
import com.google.android.gms.iid.InstanceID;

import java.io.IOException;

/**
 * Created by stefano on 08/04/16.
 */
public class Async_Register extends AsyncTask<String,Void,String> {

    //Project Number del proprio progetto Google
    private String SENDER_ID = "";

    private Activity_SplashScreen cx;
    private GoogleCloudMessaging gcm;

    public Async_Register(Activity_SplashScreen cx, String SENDER_ID) {
        super();
        this.SENDER_ID=SENDER_ID;
        this.cx=cx;
        //accedo all'API google cloud messaging
        gcm=GoogleCloudMessaging.getInstance(this.cx);
    }

    @Override
    protected String doInBackground(String... params) {
        String regid="";
        String msg = "";
        try {

            if (gcm == null)
                gcm = GoogleCloudMessaging.getInstance(cx);

            //effettuo la richiesta del register_ID
            InstanceID instanceID = InstanceID.getInstance(cx);
            regid = instanceID.getToken(SENDER_ID, GoogleCloudMessaging.INSTANCE_ID_SCOPE, null);
        }
        catch (IOException ex)
        {
            return null;
        }
        return regid;
    }

    @Override
    protected void onPostExecute(String s) {
        super.onPostExecute(s);
        if(s!=null) {

            //chiedo alla splashScreen di avviare la main activity
            cx.StartMain(s);
        }
    }
}
