package com.example.stefano.progettomaturita;

import android.app.Activity;
import android.support.design.widget.Snackbar;
import android.support.v7.widget.RecyclerView;
import android.widget.TextView;
/*
 * Created by stefano on 22/04/16.
 */
public class Async_Update_Notification extends PostRequest {

    private Activity cx;
    private String fileNotifiche;
    private Dictionary data;


    public Async_Update_Notification(String url, Dictionary data, Activity cx, String fileNotifiche) {
        super(url,data,cx);

        this.cx=cx;
        this.fileNotifiche=fileNotifiche;
        this.data=data;
    }

    @Override
    protected void onPostExecute(String s) {
        super.onPostExecute(s);

        if(!s.equals("NO_INTERNET")) {
            String Tempo = data.getItem("Tempo");
            String IdOrario = data.getItem("IDOrario");
            String IdFermata = data.getItem("IDFermata");

            if (s.equals("OK")) {
                //rimuovo la notifica dal file
                Static_Gestione_File.RemoveFromFile(fileNotifiche, IdOrario + ";" + IdFermata);
                if (Tempo != null) {
                    //se è un update riaggiungo il record al file emostro il messaggio
                    Static_Gestione_File.AppendToFile(fileNotifiche, IdOrario + ";" + IdFermata + ";" + Tempo);
                    Snackbar.make(cx.findViewById(R.id.relativeGestioneNotifiche), cx.getString(R.string.update_succes), Snackbar.LENGTH_LONG)
                            .setAction("Action", null).show();
                } else {
                    //se non è un update mostro solamente il messaggio di eliminazione
                    Snackbar.make(cx.findViewById(R.id.relativeGestioneNotifiche), cx.getString(R.string.notification_unregistered), Snackbar.LENGTH_LONG)
                            .setAction("Action", null).show();
                }

                //aggiorno l'elenco delle notifiche
                String RegID = Static_Shared_Preferences.GetString(cx, "REGID");
                Dictionary data = new Dictionary();
                data.AddItem("RegistrationID", RegID);
                new Async_Get_Iscrizioni(cx.getString(R.string.get_iscrizioni), data, cx, (RecyclerView) cx.findViewById(R.id.recycler), (TextView) cx.findViewById(R.id.lblHeadNotifiche)).execute();

            } else
                Snackbar.make(cx.findViewById(R.id.relativeGestioneNotifiche), cx.getString(R.string.notification_error), Snackbar.LENGTH_LONG)
                        .setAction("Action", null).show();
        }


    }
}
