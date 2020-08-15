package com.example.stefano.progettomaturita;

/**
 * Created by stefano on 26/07/16.
 */
public class Async_Update_Bus_Position extends PostRequest {

    Activity_Map parent;

    public Async_Update_Bus_Position(String url, Dictionary data, Activity_Map parent)
    {
        super(url,data,parent);
        this.parent=parent;
    }

    @Override
    protected void onPostExecute(final String s) {
        super.onPostExecute(s);

        //verifico che vi sia la connessione
        if(!s.equals("NO_INTERNET")) {
            new Thread(new Runnable() {
                @Override
                public void run() {
                    try {
                        //verifico che la risposta non sia vuota
                        if (!s.equals("") && !s.equals("KO")) {
                            //aggiorno la posizione
                            parent.DrawBus(s);
                            //attendo un secondo
                            Thread.sleep(1000);
                        } else {
                            //se l'autobus non è in movimento elimino un eventuale marker residuo
                            parent.RemoveBus();
                            //attendo cinque secondi
                            Thread.sleep(5000);
                        }
                    } catch (Exception ex) {

                    }
                    //aggiorno nuovamente la posizione
                    parent.UpdateBusPosition();

                }
            }).start();
        }
    }
}
