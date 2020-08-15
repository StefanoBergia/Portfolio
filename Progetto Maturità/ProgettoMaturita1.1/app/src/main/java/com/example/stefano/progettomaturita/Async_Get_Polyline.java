package com.example.stefano.progettomaturita;

import android.app.ProgressDialog;
import android.content.Context;
import android.graphics.Color;
import android.os.AsyncTask;
import com.google.android.gms.maps.CameraUpdateFactory;
import com.google.android.gms.maps.GoogleMap;
import com.google.android.gms.maps.model.LatLng;
import com.google.android.gms.maps.model.LatLngBounds;
import com.google.android.gms.maps.model.PolylineOptions;
import org.json.JSONArray;
import org.json.JSONObject;
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.net.HttpURLConnection;
import java.net.URL;
import java.util.ArrayList;
import java.util.List;
import java.util.Vector;

/**
 * Created by stefano on 24/03/16.
 */
public class Async_Get_Polyline extends AsyncTask<String, String, String> {

    //lista delle fermate che costituiscono una linea
    private Vector<Fermata> fermate;

    //lista delle coordinate che compongono la polyline
    private List<LatLng> polyz;

    //lista di supporto
    private List<LatLng> supppolyz;

    //riferimento alla mappa
    private GoogleMap map;

    private Context parent;

    private ProgressDialog pDialog;

    public Async_Get_Polyline(Context parent, GoogleMap map, Vector<Fermata> fermate){
        this.parent=parent;
        this.map=map;
        this.fermate=fermate;
        this.polyz=new ArrayList<LatLng>();
    }

    @Override
    protected void onPreExecute() {
        super.onPreExecute();

        //visualizzo la progressdialog in attesa che il percorso venga caricato
        pDialog = new ProgressDialog(parent);
        pDialog.setMessage(parent.getString(R.string.progress_msg));
        pDialog.setIndeterminate(false);
        pDialog.setCancelable(false);
        pDialog.show();

    }

    protected String doInBackground(String... args) {
        if(Static_Connection_Checker.Check(parent)) {
            //verifico che ci siano almeno due fermate all'interno della linea
            if (fermate.size() >= 2) {

                //ciclo per ogni COPPIA di fermate
                for (int i = 0; i < fermate.size() - 1; i++) {
                    //recupero ad ogni ciclo la fermata corrente e quella successiva
                    Fermata start = fermate.get(i);
                    Fermata stop = fermate.get(i + 1);

                    //genero l'url della richiesta GET
                    String stringUrl = parent.getString(R.string.google_maps) + "?origin="
                            + start.getLat()
                            + ","
                            + start.getLon()
                            + "&destination="
                            + stop.getLat()
                            + ","
                            + stop.getLon()
                            + "&sensor=false";


                    StringBuilder response = new StringBuilder();
                    try {
                        //genero e invio la richiesta
                        URL url = new URL(stringUrl);
                        HttpURLConnection httpconn = (HttpURLConnection) url.openConnection();

                        //verifico di aver ricevuto una risposta
                        if (httpconn.getResponseCode() == HttpURLConnection.HTTP_OK) {
                            BufferedReader input = new BufferedReader(new InputStreamReader(httpconn.getInputStream()), 8192);
                            String strLine = null;

                            //recupero la risposta
                            while ((strLine = input.readLine()) != null) {
                                response.append(strLine);
                            }
                            input.close();
                        }


                        String jsonOutput = response.toString();

                        //recupero la risposta e la decofifico
                        JSONObject jsonObject = new JSONObject(jsonOutput);

                        // routesArray contains ALL routes
                        JSONArray routesArray = jsonObject.getJSONArray("routes");
                        // Grab the first route
                        if (routesArray.length() > 0) {
                            JSONObject route = routesArray.getJSONObject(0);


                            JSONObject poly = route.getJSONObject("overview_polyline");
                            String polyline = poly.getString("points");

                            //recupero la lista di coordinate decodificata
                            supppolyz = decodePoly(polyline);

                            //aggiungo le coordinate all'array polyz
                            polyz.addAll(supppolyz);

                        } else
                            //se per una coppia di fermate non è stato possibile  recuperare i dati, rifaccio la richiesta
                            i--;

                    } catch (Exception e) {
                    }
                }
            }
            return "";
        }else
            return "NO_INTERNET";
    }

    protected void onPostExecute(String s) {

        if(!s.equals("NO_INTERNET")) {

            int i = 0;
            LatLng pos;

            //inizio a creare la polyline
            PolylineOptions opt = new PolylineOptions().width(8).color(Color.rgb(68, 138, 255));

            //aggiungo tutte le coordinate estratte in precedenza alla polyline
            for (i = 0; i < polyz.size(); i++) {
                pos = polyz.get(i);
                opt.add(pos);
            }

            //disegno la polyline
            map.addPolyline(opt);

            //centro la visualizzazione del percorso
            LatLngBounds.Builder boundsBuilder = new LatLngBounds.Builder();
            boundsBuilder.include(polyz.get(0));
            boundsBuilder.include(polyz.get(i - 1));
            LatLngBounds bounds = boundsBuilder.build();
            map.moveCamera(CameraUpdateFactory.newLatLngBounds(bounds, 20));

            //chiudo la progressdialog
            pDialog.dismiss();
        }

    }

    /* Method to decode polyline points */
    private List<LatLng> decodePoly(String encoded) {

        List<LatLng> poly = new ArrayList<LatLng>();
        int index = 0, len = encoded.length();
        int lat = 0, lng = 0;

        while (index < len) {
            int b, shift = 0, result = 0;
            do {
                b = encoded.charAt(index++) - 63;
                result |= (b & 0x1f) << shift;
                shift += 5;
            } while (b >= 0x20);
            int dlat = ((result & 1) != 0 ? ~(result >> 1) : (result >> 1));
            lat += dlat;

            shift = 0;
            result = 0;
            do {
                b = encoded.charAt(index++) - 63;
                result |= (b & 0x1f) << shift;
                shift += 5;
            } while (b >= 0x20);
            int dlng = ((result & 1) != 0 ? ~(result >> 1) : (result >> 1));
            lng += dlng;

            LatLng p = new LatLng((((double) lat / 1E5)),
                    (((double) lng / 1E5)));
            poly.add(p);
        }

        return poly;
    }
}