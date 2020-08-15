package com.example.stefano.progettomaturita;

import android.app.Activity;
import android.content.Context;
import android.support.design.widget.Snackbar;
import android.support.v7.widget.RecyclerView;
import android.widget.TextView;
import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;
import java.util.Vector;

/**
 * Created by luca on 27/05/2016.
 */
public class Async_Get_Iscrizioni extends PostRequest {

    Context cx;
    RecyclerView rv;
    TextView head;

    public Async_Get_Iscrizioni(String url, Dictionary data, Context cx, RecyclerView rv, TextView head)
    {
        super(url,data,cx);
        this.rv = rv;
        this.cx = cx;
        this.head = head;
    }

    @Override protected void onPostExecute(String ritorno)
    {
        if(!ritorno.equals("NO_INTERNET")) {
            if (ritorno.equals("0")) {
                //non ci sono notifiche registrate
                head.setText(cx.getString(R.string.empty_msg));
                head.setTextSize(14);
                head.setGravity(1);
                rv.setAdapter(null);
            } else if (!ritorno.equals("KO")) {
                try {
                    //se sono presenti delle notifiche registrate, decodifico il risultato per estrarre i dati
                    JSONObject obj = new JSONObject(ritorno);
                    JSONArray array = null;

                    array = obj.getJSONArray("notifiche");

                    Vector<Support_Card_Gestione_Iscrizioni> iscrizioni = new Vector<Support_Card_Gestione_Iscrizioni>();
                    Support_Card_Gestione_Iscrizioni supp = null;

                    for (int i = 0; i < array.length(); i++) {
                        JSONObject s = array.getJSONObject(i).getJSONObject("notifica");

                        supp = new Support_Card_Gestione_Iscrizioni();
                        supp.setIDLinea(s.getString("IDLinea"));
                        supp.setIDOrario(s.getString("IDOrario"));
                        supp.setNomeLinea(s.getString("nomeLinea"));
                        supp.setRagSoc(s.getString("ragSoc"));
                        supp.setNomeFermata(s.getString("nomeFermata"));
                        supp.setOrario(s.getString("orario"));
                        supp.setTempo(s.getString("tempo"));
                        supp.setIDFermata(s.getString("fermata"));
                        supp.setParent((Interface_Open_Detail) cx);

                        iscrizioni.add(supp);
                    }

                    //popolo la recyclerView
                    Adapter_Registrazioni adapter = new Adapter_Registrazioni(iscrizioni, (Activity_Gestione_Notifiche) cx);
                    rv.setAdapter(adapter);

                    head.setText(cx.getString(R.string.full_msg));
                    head.setTextSize(18);
                    head.setGravity(0);

                } catch (JSONException jsonEx) {
                    jsonEx.getMessage();
                    Snackbar.make(((Activity) cx).findViewById(R.id.relativeGestioneNotifiche),
                            cx.getString(R.string.gestione_notifiche_err), Snackbar.LENGTH_LONG).
                            setAction("Action", null).show();
                }
            }
        }else
            Snackbar.make(((Activity) cx).findViewById(R.id.relativeGestioneNotifiche),
                    cx.getString(R.string.no_internet_2), Snackbar.LENGTH_LONG).
                    setAction("Action", null).show();

    }

}
