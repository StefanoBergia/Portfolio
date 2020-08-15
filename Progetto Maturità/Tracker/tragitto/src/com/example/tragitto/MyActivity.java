package com.example.tragitto;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.location.Location;
import android.location.LocationManager;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.GridView;
import android.widget.Toast;

import java.util.ArrayList;
import java.util.List;

public class MyActivity extends Activity {
    /**
     * Called when the activity is first created.
     */
    EditText nomeTappe;
    EditText nomeFermata;
    Button btnstart;
    Button btnstop;
    Button btnfermata;
    TextAdapter txtadp;
    ArrayList<String> vect;
    GridView grid;

    Context c;
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);
        nomeTappe=(EditText)findViewById(R.id.nomeTappe);
        nomeFermata=(EditText)findViewById(R.id.nomeFermata);
        btnstart=(Button)findViewById(R.id.btnStart);
        btnfermata=(Button)findViewById(R.id.btnFermata);
        btnstop=(Button)findViewById(R.id.btnStop);
        grid=(GridView)findViewById(R.id.grid);
        txtadp=new TextAdapter(this);
       grid.setAdapter(txtadp);
        txtadp.AddItem("LAT");
        txtadp.AddItem("LON");
        txtadp.AddItem("NAME");
        if(savedInstanceState!=null && savedInstanceState.getBoolean("startlocked"))
        {
            nomeTappe.setEnabled(false);
            btnstart.setEnabled(false);
            btnfermata.setEnabled(true);
        }else {
            btnstop.setEnabled(false);
            btnfermata.setEnabled(false);
        }
        if(savedInstanceState!=null && savedInstanceState.getStringArrayList("fermate")!=null)
        {
            vect =savedInstanceState.getStringArrayList("fermate");
        }else
        {
            vect =new ArrayList<String>();
            vect.add("LAT");
            vect.add("LON");
            vect.add("NAME");
        }

        c=this;

    }

    public void StartTappe(View v){
        if(!nomeTappe.getText().toString().equals("")){
            Intent serv=new Intent(getBaseContext(), Tracker.class);
            serv.putExtra("file_name",nomeTappe.getText().toString());
            startService(serv);
            nomeTappe.setEnabled(false);
            btnstart.setEnabled(false);
            btnstop.setEnabled(true);
            btnfermata.setEnabled(true);


        }else
            Toast.makeText(this,"Inserisci il nome del file",Toast.LENGTH_SHORT).show();

    }

    public void StopTappe(View v){
        stopService(new Intent(getBaseContext(), Tracker.class));
        nomeTappe.setEnabled(true);
        btnstart.setEnabled(true);

        btnstop.setEnabled(false);
        btnfermata.setEnabled(false);
        grid.setAdapter(null);
        vect.clear();
    }

    public void SaveFermata(View v){
        if(!nomeTappe.getText().toString().equals("")){
            if(!nomeFermata.getText().toString().equals("")){
              LocationManager  locationManager = (LocationManager)getSystemService(Context.LOCATION_SERVICE);
                List<String> providers = locationManager.getAllProviders();
                Location loc=null;

                for (int i = 0; i < providers.size(); i++)
                    if(locationManager.getLastKnownLocation(providers.get(i))!=null && (loc==null || locationManager.getLastKnownLocation(providers.get(i)).getTime()>loc.getTime()))
                       loc = locationManager.getLastKnownLocation(providers.get(i));
                if(loc!=null)
                    new FermateAsync(vect,grid).execute("Fermate_"+nomeTappe.getText().toString(),loc.getLatitude()+"",loc.getLongitude()+"",nomeFermata.getText().toString());
            }else
                Toast.makeText(this,"Inserisci il nome della fermata",Toast.LENGTH_SHORT).show();
        }else
            Toast.makeText(this,"Inserisci il nome del file",Toast.LENGTH_SHORT).show();

    }

    protected void onSaveInstanceState(Bundle icicle) {
        super.onSaveInstanceState(icicle);
        icicle.putBoolean("startlocked", btnstop.isEnabled());
        icicle.putStringArrayList("fermate", vect);
    }


}
