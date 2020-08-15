package com.example.stefano.progettomaturita;

import android.content.Context;
import android.support.v7.widget.LinearLayoutManager;
import android.support.v7.widget.RecyclerView;
import android.widget.TextView;
import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;
import java.util.Vector;

/**
 * Created by stefano on 05/02/16.
 */
public class Async_Get_Linee extends PostRequest {

    //RecyclerView per visualizzare i risultati della ricerca
    private RecyclerView rv;

    private Context cx;
    private TextView lblMsg;

    //Array per memorizzare le informazioni da visualizzare
    private Vector<Support_Card_Linea> linee;

    public Async_Get_Linee(String url, Dictionary data, Context cx, RecyclerView rv, TextView lblMsg)
    {
        super(url,data,cx);
        this.rv=rv;
        this.cx=cx;
        this.lblMsg=lblMsg;
        this.linee=null;
    }

    @Override
    protected void onPostExecute(String s) {
        super.onPostExecute(s);
        if(!s.equals("NO_INTERNET")) {
            if (s.equals("KO") || s.equals("")) {
                //informo l'utente che non ci sono risultati
                lblMsg.setText(cx.getString(R.string.no_results));
            } else {
                lblMsg.setText("");

                //inizializzo il vettore
                linee = new Vector<>();

                try {
                    //Deserializzo la risposta
                    JSONObject obj = new JSONObject(s);
                    JSONObject supp;
                    Support_Card_Linea linea;
                    JSONArray array = obj.getJSONArray("linee");
                    for (int i = 0; i < array.length(); i++) {
                        supp = (JSONObject) array.get(i);
                        linea = new Support_Card_Linea();
                        linea.setIDLinea(supp.getString("IDLinea"));
                        linea.setIDOrario(supp.getString("IDOrario"));
                        linea.setNomeLinea(supp.getString("Nome"));
                        linea.setOra(supp.getString("Ora"));
                        linea.setDitta(supp.getString("Ditta"));
                        linea.setParent((Interface_Open_Detail) cx);
                        linee.add(linea);
                    }

                } catch (JSONException jsonex) {
                }


                //assegno l'adapter alla recyclerView
                LinearLayoutManager llm = new LinearLayoutManager(cx);
                rv.setLayoutManager(llm);
                Adpater_Linee adapter = new Adpater_Linee(linee, cx);
                rv.setAdapter(adapter);
            }
        }else
        {
            lblMsg.setText(cx.getString(R.string.no_internet_2));
        }
    }
}
