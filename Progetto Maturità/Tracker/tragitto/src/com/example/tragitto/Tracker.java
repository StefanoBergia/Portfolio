package com.example.tragitto;

import android.app.Service;
import android.content.Context;
import android.content.Intent;
import android.location.Location;
import android.location.LocationListener;
import android.location.LocationManager;
import android.os.*;
import android.widget.Toast;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.net.URL;
import java.net.URLConnection;
import java.net.URLEncoder;

/**
 * Created by admin on 11/01/2016.
 */
public class Tracker extends Service {

    LocationManager locationManager;
    LocationListener listener;
    Context c=this;
    Intent params;
    long baseTime=0;
    long support=0;
    PowerManager.WakeLock wl;
    PowerManager pm;

    @Override
    public IBinder onBind(Intent intent) {
        return null;
    }

    @Override
    public int onStartCommand(Intent intent, int flags, int startId) {

        params=intent;
        pm = (PowerManager)getApplicationContext().getSystemService(
                getApplicationContext().POWER_SERVICE);
        wl = pm.newWakeLock(PowerManager.PARTIAL_WAKE_LOCK, "TAG");
        wl.acquire();
        StartTracking();
        return START_STICKY;
    }

    @Override
    public void onDestroy() {
        super.onDestroy();
        locationManager.removeUpdates(listener);
        wl.release();
        Toast.makeText(this, "Service Destroyed", Toast.LENGTH_LONG).show();
    }

    public void StartTracking(){
        locationManager = (LocationManager)getSystemService(Context.LOCATION_SERVICE);
        baseTime= System.currentTimeMillis();
        support=0;
        listener= new LocationListener() {
            @Override
            public void onLocationChanged(Location location) {
                new Thread(new Runnable() {
                    @Override
                    public void run() {
                        try {
                            String Data = URLEncoder.encode("file_name", "UTF-8") + "=" + URLEncoder.encode(params.getStringExtra("file_name"));
                            Data += "&" + URLEncoder.encode("LAT", "UTF-8") + "=" + URLEncoder.encode(location.getLatitude()+"");
                            Data += "&" + URLEncoder.encode("LON", "UTF-8") + "=" + URLEncoder.encode(location.getLongitude()+"");
                            support=System.currentTimeMillis()- baseTime;
                            baseTime+=support;
                            Data += "&" + URLEncoder.encode("TIME", "UTF-8") + "=" + URLEncoder.encode((support)+"");
                            URLConnection cn= new URL("http://bustracker.altervista.org/memorizzatappe.php").openConnection();
                            cn.setDoOutput(true);
                            OutputStreamWriter sw = new OutputStreamWriter(cn.getOutputStream());
                            sw.write(Data);
                            sw.flush();
                            sw.close();
                            String s="";
                            String supp;
                            BufferedReader reader = new BufferedReader(new InputStreamReader(cn.getInputStream()));
                            supp=reader.readLine();
                            while(supp!=null)
                            {
                                s+=supp;
                                supp=reader.readLine();
                            }
                            Handler handler = new Handler(Looper.getMainLooper());
                            handler.post(new Runnable() {
                                @Override
                                public void run() {

                                    Toast.makeText(c,"LAT:"+location.getLatitude()+"\nLON:"+location.getLongitude()+"\nTIME:"+support , Toast.LENGTH_SHORT).show();
                                }
                            });

                        }catch (Exception e){

                        }
                    }
                }).start();
            }

            @Override
            public void onStatusChanged(String provider, int status, Bundle extras) {

            }

            @Override
            public void onProviderEnabled(String provider) {

            }

            @Override
            public void onProviderDisabled(String provider) {

            }
        };
        locationManager.requestLocationUpdates(LocationManager.GPS_PROVIDER, 1500, 100, listener);
    }


}
