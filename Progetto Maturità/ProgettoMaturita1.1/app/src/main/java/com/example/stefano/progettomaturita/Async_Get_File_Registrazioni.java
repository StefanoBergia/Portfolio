package com.example.stefano.progettomaturita;

import android.content.Context;

import java.util.StringTokenizer;

/**
 * Created by stefano on 25/07/16.
 */
public class Async_Get_File_Registrazioni extends PostRequest {

    private Context cx;

    public Async_Get_File_Registrazioni(String url, Dictionary data, Context cx)
    {
        super(url,data,cx);
        this.cx=cx;
    }

    @Override
    protected void onPostExecute(String s) {
        super.onPostExecute(s);
        String filename=cx.getFilesDir()+"/"+cx.getString(R.string.saved_n);
        if(!s.equals("")) {
            //svuoto il file
            Static_Gestione_File.EreaseFileContent(filename);
            //ripopolo il file con i valori aggiornati sul server
            StringTokenizer st = new StringTokenizer(s, "?");
            if(st.countTokens()>1)
                while (st.hasMoreTokens())
                    Static_Gestione_File.AppendToFile(filename, st.nextToken());
            else
                Static_Gestione_File.AppendToFile(filename, s.substring(0,s.length()-1));
        }


    }
}
