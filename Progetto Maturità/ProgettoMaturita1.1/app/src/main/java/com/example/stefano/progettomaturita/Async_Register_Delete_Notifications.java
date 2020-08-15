package com.example.stefano.progettomaturita;

import android.support.design.widget.Snackbar;

/**
 * Created by stefano on 22/04/16.
 */
public class Async_Register_Delete_Notifications extends PostRequest {

    private Activity_Detail parent;
    private Dictionary data;
    private String fileNotifiche;


    public Async_Register_Delete_Notifications(String url, Dictionary data, Activity_Detail parent, String fileNotifiche) {
        super(url,data,parent);
        this.parent=parent;
        this.data=data;
        this.fileNotifiche=fileNotifiche;
    }

    @Override
    protected void onPostExecute(String s) {
        super.onPostExecute(s);

        if(!s.equals("NO_INTERNET")) {
            //recupero i dati dal dictionary
            String Tempo = data.getItem("Tempo");
            String IdOrario = data.getItem("IDOrario");
            String IdFermata = data.getItem("IDFermata");

            if (s.equals("OK")) {

                if (Tempo != null) {
                    //se la notifica è stata aggiunga, aggiorno il file delle notifiche (e im colore di sfondo)
                    Static_Gestione_File.AppendToFile(fileNotifiche, IdOrario + ";" + IdFermata + ";" + Tempo + "\n");
                    parent.getCurrentFermataView().setBgColor();

                    Snackbar.make(parent.findViewById(R.id.rel), parent.getString(R.string.notification_registered), Snackbar.LENGTH_LONG)
                            .setAction("Action", null).show();
                } else {
                    //se la notifica è stata rimossa, aggiorno il file delle notifiche (e im colore di sfondo)
                    Static_Gestione_File.RemoveFromFile(fileNotifiche, IdOrario + ";" + IdFermata);
                    parent.getCurrentFermataView().resetBgColor();

                    Snackbar.make(parent.findViewById(R.id.rel), parent.getString(R.string.notification_unregistered), Snackbar.LENGTH_LONG)
                            .setAction("Action", null).show();
                }
            } else
                Snackbar.make(parent.findViewById(R.id.rel), parent.getString(R.string.notification_error), Snackbar.LENGTH_LONG)
                        .setAction("Action", null).show();
        }else {
            Snackbar.make(parent.findViewById(R.id.rel), parent.getString(R.string.no_internet_2), Snackbar.LENGTH_LONG)
                    .setAction("Action", null).show();
        }
    }
}
