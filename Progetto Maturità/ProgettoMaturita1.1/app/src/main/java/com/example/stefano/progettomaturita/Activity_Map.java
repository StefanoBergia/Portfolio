package com.example.stefano.progettomaturita;

import android.content.Context;
import android.content.Intent;
import android.graphics.Color;
import android.graphics.Typeface;
import android.support.design.widget.FloatingActionButton;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.view.Gravity;
import android.view.MenuItem;
import android.view.View;
import android.widget.LinearLayout;
import android.widget.TextView;
import com.google.android.gms.maps.CameraUpdateFactory;
import com.google.android.gms.maps.GoogleMap;
import com.google.android.gms.maps.OnMapReadyCallback;
import com.google.android.gms.maps.SupportMapFragment;
import com.google.android.gms.maps.model.BitmapDescriptorFactory;
import com.google.android.gms.maps.model.LatLng;
import com.google.android.gms.maps.model.LatLngBounds;
import com.google.android.gms.maps.model.Marker;
import com.google.android.gms.maps.model.MarkerOptions;
import org.json.JSONObject;
import java.util.ArrayList;
import java.util.Vector;

public class Activity_Map extends AppCompatActivity implements OnMapReadyCallback,GoogleMap.OnMarkerClickListener {

    //riferimento all'ogggetto googlemaps
    private GoogleMap mMap;

    //argomenti dell'intent
    private Bundle args;

    //vettore delle fermate che compongono la linea
    private Vector<Fermata> fermate;

    //variabile booleana utilizzata per bloccare l'aggiornamento della posizione dell'autobus
    private boolean stopBus;

    //riferimento al marker rappresentante la posizione dell'autobus
    private Marker busMarker;

    private Activity_Map selfref;

    private FloatingActionButton btn;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_map_linea);

        //recupero gli argomenti dell'intent
        args=getIntent().getExtras();

        stopBus=false;
        busMarker=null;
        selfref=this;

        //avvio il rendering della mappa
        SupportMapFragment mapFragment = (SupportMapFragment) getSupportFragmentManager().findFragmentById(R.id.map);
        mapFragment.getMapAsync(this);

        //imposto il titolo dell'activity
        setTitle(args.getString("NomeLinea"));

        //recupero la lista delle fermate dall'intent e la deserializzo per poi memorizzarla nel vettore fermate
        fermate=new Vector<Fermata>();
        Fermata supp=null;
        ArrayList<String> argsFermate=args.getStringArrayList("Fermate");

        for(int i=0;i<argsFermate.size();i++)
        {
            supp=new Fermata();
            supp.DeSerialize(argsFermate.get((i)));
            fermate.add(supp);
        }

        //rimuovo le fermate dalla lista degli argomenti
        args.remove("Fermate");

        btn=(FloatingActionButton)findViewById(R.id.locate);

    }

    //questo metodo viene richiamato automaticamente una volta terminato il rendering della mappa
    @Override
    public void onMapReady(GoogleMap googleMap) {

        //recupero l'oggetto rappresentante la mappa
        mMap = googleMap;

        //imposto l'activity stessa come responsabile per la gestione dei click sui marker visualizzati sulla mappa
        googleMap.setOnMarkerClickListener(this);

        //imposto i riquadri da visualizzare sui marker
        setInfoWindow();

        LatLng pos;

        //individuo le fermate sulla mappa attraverso un marker
        for(int i=0;i<fermate.size();i++){

            //recupero le coordinate della fermata
            pos=new LatLng(Double.parseDouble(fermate.get(i).getLat()),Double.parseDouble(fermate.get(i).getLon()));

            //disegno il marker
            mMap.addMarker(new MarkerOptions().
                    position(pos).
                    title(fermate.get(i).getLocalita()).
                    snippet(fermate.get(i).getNome() + "\n"+getString(R.string.ora) + fermate.get(i).getOra()).
                    icon(BitmapDescriptorFactory.defaultMarker(BitmapDescriptorFactory.HUE_AZURE)));

        }

        //nel momento in cui si preme l'action Button, il percorso viene centrato all'interno dello schermo
        btn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                LatLngBounds.Builder boundsBuilder = new LatLngBounds.Builder();
                boundsBuilder.include(new LatLng(Double.parseDouble(fermate.get(0).getLat()),Double.parseDouble(fermate.get(0).getLon())));
                boundsBuilder.include(new LatLng(Double.parseDouble(fermate.lastElement().getLat()),Double.parseDouble(fermate.lastElement().getLon())));
                LatLngBounds bounds = boundsBuilder.build();
                mMap.moveCamera(CameraUpdateFactory.newLatLngBounds(bounds, 20));
            }
        });

        //disegno il percorso sulla mappa attraverso una polyline
        new Async_Get_Polyline(this, mMap,fermate).execute();

        //disegna autobus in movimento
        UpdateBusPosition();
    }

    //questo metodo aggiorna la posizione dell'autobus in movimento
    public void UpdateBusPosition(){
        this.runOnUiThread(new Runnable() {
            @Override
            public void run() {
                if(!stopBus){
                    Dictionary data=new Dictionary();
                    data.AddItem("IDOrario",args.getString("IDOrario"));
                    new Async_Update_Bus_Position(getString(R.string.get_bus),data,selfref).execute();
                }
            }
        });

    }

    @Override
    public boolean onMarkerClick(Marker theMarker)
    {
        //permetto di visualizzare solo le infowindow dei marker relativi alle fermate
        //non del marker dell'autobus

        if(!theMarker.getTitle().equals("Posizione Corrente"))
            //nasconde infowindow
            return false;
        else
            //mostra infowindow
            return  true;
    }


    //elimina il marker dell'autobus
    public void RemoveBus(){
        this.runOnUiThread(new Runnable() {
            @Override
            public void run() {
                if(busMarker!=null)
                {

                    busMarker.remove();
                    busMarker=null;
                }
            }
        });
    }


    //disegna il marker dell'autobus alla posizione specificata
    public void DrawBus(final String obj){
        this.runOnUiThread(new Runnable() {
            @Override
            public void run() {
                try{

                    //recupero le coordinate dell'autobus
                    JSONObject bus=new JSONObject(obj);
                    LatLng pos=new LatLng(bus.getDouble("Latitude"),bus.getDouble("Longitude"));

                    //elimino il vecchio marker
                    RemoveBus();

                    //creo il nuovo marker con la posizione aggiornata
                    busMarker=mMap.addMarker(new MarkerOptions().
                            position(pos).
                            title("Posizione Corrente").
                            icon(BitmapDescriptorFactory.fromResource(R.drawable.bus)));
                }catch(Exception ex){}
            }
        });
    }

    public boolean onOptionsItemSelected(MenuItem item) {
        switch (item.getItemId()) {
            // Respond to the action bar's Up/Home button
            case android.R.id.home:
                stopBus=true;
                Intent intent= new Intent(Activity_Map.this,Activity_Detail.class);
                intent.putExtras(args);
                startActivity(intent);
                return true;
        }
        return super.onOptionsItemSelected(item);
    }

    @Override
    public void onBackPressed() {
        super.onBackPressed();
        stopBus=true;
        Intent intent= new Intent(Activity_Map.this,Activity_Detail.class);
        intent.putExtras(args);
        startActivity(intent);
    }

    //metodo che descrive come andranno ad essere strutturate le infowindows visualizzate sui marker
    public void setInfoWindow(){
        mMap.setInfoWindowAdapter(new GoogleMap.InfoWindowAdapter() {

            @Override
            public View getInfoWindow(Marker arg0) {
                return null;
            }

            @Override
            public View getInfoContents(Marker marker) {

                Context context = getApplicationContext();

                LinearLayout info = new LinearLayout(context);
                info.setOrientation(LinearLayout.VERTICAL);

                TextView title = new TextView(context);
                title.setTextColor(Color.BLACK);
                title.setGravity(Gravity.CENTER);
                title.setTypeface(null, Typeface.BOLD);

                //recupero il titolo del marker
                title.setText(marker.getTitle());

                TextView snippet = new TextView(context);
                snippet.setTextColor(Color.GRAY);
                snippet.setGravity(Gravity.CENTER);

                //recupero il testo del  marker
                snippet.setText(marker.getSnippet());

                //aggiungo gli elementi creati al layout contenitore
                info.addView(title);
                info.addView(snippet);

                return info;
            }
        });
    }
}
