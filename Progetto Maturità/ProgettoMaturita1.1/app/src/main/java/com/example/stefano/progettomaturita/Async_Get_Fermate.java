package com.example.stefano.progettomaturita;


import android.support.v7.widget.LinearLayoutManager;
import android.support.v7.widget.RecyclerView;
import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.util.StringTokenizer;
import java.util.Vector;

/**
 * Created by stefano on 05/02/16.
 */
public class Async_Get_Fermate extends PostRequest {

    //RecyclerView in cui verranno visualizzate le informazioni riguardanti le fermate
    private RecyclerView rv;
    private Activity_Detail parent;

    //nome del file delle notifiche
    private String fileNotifiche;
    //nome del file dei preferiti
    private String filePreferiti;

    //dati
    private String currentData;

    private String idOrario;

    //Array contenente tutte le informazioni riguardanti le fermate
    private Vector<Fermata> fermate;

    public Async_Get_Fermate(String url, Dictionary data, Activity_Detail parent, RecyclerView rv, String fileNotifiche, String filePreferiti, String currentData)
    {
        super(url,data,parent);
        this.rv=rv;
        this.parent=parent;
        this.fileNotifiche=fileNotifiche;
        this.fermate=null;
        this.idOrario=data.getItem("IDOrario");
        this.filePreferiti=filePreferiti;
        this.currentData=currentData;
    }

    @Override
    protected void onPostExecute(String s) {
        super.onPostExecute(s);

        if (!s.equals("") && !s.equals("KO")) {

            if(!s.equals("NO_INTERNET")) {
                //passo al parent l'oggetto json contenente le fermate
                parent.AppendFermate(s);

            }else
            {
                //se non c'è connessione recupero i dati dai preferiti
                String data= Static_Gestione_File.Get(filePreferiti,currentData);
                if(data!=null)
                {
                    StringTokenizer st= new StringTokenizer(data,";");
                    String json="";
                    for(int i=0;i<6;i++)
                        json=st.nextToken();
                    s=json;
                }


            }
            fermate = new Vector<>();

            //recupero le notifiche salvate
            Vector<String> notifiche = Static_Gestione_File.GetSaved(fileNotifiche);

            //array di supporto
            Vector<String> notSupp = new Vector<String>();

            try {
                //decodifico la stringa JSON restituita dal server
                JSONObject obj = new JSONObject(s);

                JSONObject supp;
                Fermata fermata;

                JSONArray array = obj.getJSONArray("fermate");

                for (int i = 0; i < array.length(); i++) {

                    supp = (JSONObject) array.get(i);
                    fermata = new Fermata();
                    fermata.setIDFermata(supp.getString("ID"));
                    fermata.setOra(supp.getString("Ora"));
                    fermata.setLat(supp.getString("Lat"));
                    fermata.setLon(supp.getString("Lon"));
                    fermata.setLocalita(supp.getString("NomeLocalita"));
                    fermata.setNome(supp.getString("NomeFermata"));
                    fermate.add(fermata);

                    //verifico se sulla fermata è registrata una notifica
                    boolean added = false;
                    for (int j = 0; j < notifiche.size(); j++) {
                        if (notifiche.get(j).startsWith(idOrario + ";" + fermata.getIDFermata())) {
                            //se la notifica è registrata, aggiungo un 'OK' all'array di supporto
                            notSupp.add("OK");
                            added = true;
                            break;
                        }

                    }
                    if (!added)
                        //se la notifica è registrata, aggiungo un 'KO' all'array di supporto
                        notSupp.add("KO");

                }

            } catch (JSONException jsonex) {
            }

            //inizializzo la recyclerView
            LinearLayoutManager llm = new LinearLayoutManager(parent);
            rv.setLayoutManager(llm);

            //popolo la recyclerview
            Adapter_Fermata adapter = new Adapter_Fermata(parent, fermate, notSupp);
            rv.setAdapter(adapter);

            int scroll = 0;
            rv.setVerticalScrollbarPosition(scroll);

            //restituisco alla
            parent.setFermate(fermate);



        }


    }

}

