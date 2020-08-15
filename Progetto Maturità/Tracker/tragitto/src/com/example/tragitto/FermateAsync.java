package com.example.tragitto;

import android.os.AsyncTask;
import android.widget.GridView;
import android.widget.Toast;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.net.URL;
import java.net.URLConnection;
import java.net.URLEncoder;
import java.util.ArrayList;

/**
 * Created by stefano on 12/01/16.
 */
public class FermateAsync extends AsyncTask<String,Void,String> {

    String lat;
    String lon;
    String Name;
    ArrayList<String> txtadp;
    GridView v;

    public FermateAsync(ArrayList<String> txtadp, GridView v){
        this.txtadp=txtadp;
        this.v=v;
    }

    @Override
    protected String doInBackground(String... params) {
        String fileName=params[0];
        lat=params[1];
        lon=params[2];
        Name=params[3];
        try {
            String Data = URLEncoder.encode("file_name", "UTF-8") + "=" + URLEncoder.encode(fileName);
            Data += "&" + URLEncoder.encode("LAT", "UTF-8") + "=" + URLEncoder.encode(lat);
            Data += "&" + URLEncoder.encode("LON", "UTF-8") + "=" + URLEncoder.encode(lon);
            Data += "&" + URLEncoder.encode("NAME", "UTF-8") + "=" + URLEncoder.encode(Name);
            URLConnection cnn = new URL("http://bustracker.altervista.org/memorizzafermate.php").openConnection();
            cnn.setDoOutput(true);
            OutputStreamWriter sw = new OutputStreamWriter(cnn.getOutputStream());
            sw.write(Data);
            sw.flush();
            sw.close();
            String s="";
            String supp;
            BufferedReader reader = new BufferedReader(new InputStreamReader(cnn.getInputStream()));
            supp=reader.readLine();
            while(supp!=null)
            {
                s+=supp;
                supp=reader.readLine();
            }
            reader.close();
        }catch(Exception e){}
        return null;
    }

    @Override
    protected void onPostExecute(String s) {
        super.onPostExecute(s);
        txtadp.add(lat);
        txtadp.add(lon);
        txtadp.add(Name);
        TextAdapter adp=new TextAdapter(v.getContext());
        for (int i=0;i<txtadp.size();i++)
            adp.AddItem(txtadp.get(i));
        v.setAdapter(adp);
    }
}
