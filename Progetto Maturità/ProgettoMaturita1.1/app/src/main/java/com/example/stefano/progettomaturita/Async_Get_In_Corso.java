package com.example.stefano.progettomaturita;

import android.support.v7.widget.CardView;
import android.view.View;
import android.widget.TextView;
import org.json.JSONException;
import org.json.JSONObject;

/**
 * Created by stefano on 11/03/16.
 */
public class Async_Get_In_Corso extends PostRequest
{


    private CardView cv;
    private TextView autista;
    private TextView autobus;
    private TextView ritardotxt;


    public Async_Get_In_Corso(String url, Dictionary data, CardView cv, TextView autista, TextView autobus, TextView ritardoTxt) {
        super(url,data,cv.getContext());
        this.cv = cv;
        this.autista = autista;
        this.autobus = autobus;
        this.ritardotxt = ritardoTxt;

        //nascondo momentaneamente la CardView
        cv.setVisibility(View.GONE);
    }

    @Override
    protected void onPostExecute(String s) {
        super.onPostExecute(s);

        // variabile per contenere il ritardo
        int ritardo=0;

        if(!s.equals("") && !s.equals("NO_INTERNET"))
        {
            try {
                //decodifico la stringa JSON restituita e visualizzo i dati nel layout
                JSONObject obj = new JSONObject(s);
                autista.setText(cv.getContext().getString(R.string.driver)+obj.getString("Autista"));
                autobus.setText(cv.getContext().getString(R.string.bus)+obj.getString("IDAutobus"));


                //recupero il ritardo, lo converto in minuti e lo visualizzo
                ritardo=obj.getInt("Ritardo");
                ritardo=(int)(ritardo/60000);
                ritardotxt.setText(cv.getContext().getString(R.string.delay)+ritardo+" min.");

                //rendo la cardview visibile
                cv.setVisibility(View.VISIBLE);

            }catch(JSONException jsonex){
                cv.setVisibility(View.GONE);
            }
        }
    }
}

