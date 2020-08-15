package com.example.stefano.progettomaturita;

import android.content.Context;
import android.os.AsyncTask;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.UnsupportedEncodingException;
import java.net.MalformedURLException;
import java.net.URL;
import java.net.URLConnection;
import java.net.URLEncoder;

/**
 * Created by stefano on 25/07/16.
 */

//classe base per tutte le classi che effettuano delle richieste post al server
public abstract class PostRequest extends AsyncTask<String,Void,String> {

    //url della risorsa da reperire
    protected String urlString;
    //parametri della richiesta
    protected Dictionary parameters;

    protected Context context;

    public PostRequest(String urlString,Dictionary parameters,Context cx){
        this.urlString=urlString;
        this.parameters=parameters;
        this.context =cx;
    }

    @Override
    protected String doInBackground(String... params) {
        if(Static_Connection_Checker.Check(context)) {
            String ret = "";
            try {

                String data = "";

                if (parameters != null) {
                    //compongo i parametri della richiesta
                    for (int i = 0; i < parameters.getLength(); i++) {
                        data += URLEncoder.encode(parameters.getKeyAt(i), "UTF-8") + "=" + URLEncoder.encode(parameters.getItemAt(i), "UTF-8");
                        if (i < parameters.getLength() - 1)
                            data += "&";
                    }
                }

                //eseguo la richiesta
                URL url = new URL(urlString);
                URLConnection cnn = url.openConnection();
                cnn.setDoOutput(true);
                OutputStreamWriter sw = new OutputStreamWriter(cnn.getOutputStream());
                sw.write(data);
                sw.flush();
                sw.close();
                BufferedReader sr = new BufferedReader(new InputStreamReader(cnn.getInputStream()));
                String supp = "";
                supp = sr.readLine();
                while (supp != null) {
                    ret += supp;
                    supp = sr.readLine();
                }
                sr.close();

            } catch (UnsupportedEncodingException unex) {
                ret = "KO";
            } catch (MalformedURLException mex) {
                ret = "KO";
            } catch (IOException ioex) {
                ret = "KO";
            } catch (Exception ex) {
                ret = "KO";
            }

            return ret;
        }else
            return "NO_INTERNET";
    }
}
