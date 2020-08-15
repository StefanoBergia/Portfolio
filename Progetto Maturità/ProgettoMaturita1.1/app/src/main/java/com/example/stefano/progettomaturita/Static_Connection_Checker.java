package com.example.stefano.progettomaturita;

import android.content.Context;
import android.net.ConnectivityManager;
import android.net.NetworkInfo;

/**
 * Created by stefano on 29/07/16.
 */
public class Static_Connection_Checker {


    //restituisce lo stato della connessione
    public static boolean Check(Context cx)
    {
        ConnectivityManager cm = (ConnectivityManager)cx.getSystemService(Context.CONNECTIVITY_SERVICE);

        NetworkInfo activeNetwork = cm.getActiveNetworkInfo();
        boolean isConnected = activeNetwork != null &&
                activeNetwork.isConnectedOrConnecting();

        String fileUpdated=Static_Shared_Preferences.GetString(cx,"FILE_UPDATED");

        if(isConnected  && fileUpdated.equals("KO") )
        {
            //se la connessione è attiva, recupero le notifiche a cui sono registrato dal server
            Dictionary data=new Dictionary();
            data.AddItem("RegID",Static_Shared_Preferences.GetString(cx,"REGID"));
            new Async_Get_File_Registrazioni(cx.getString(R.string.get_notifiche),data,cx).execute();
            //memorizzo il fatto che il file delle notifiche è aggiornato
            Static_Shared_Preferences.PutString(cx,"FILE_UPDATED","OK");

        }else if(!isConnected )
        {
            Static_Shared_Preferences.PutString(cx,"FILE_UPDATED","KO");
        }

        return isConnected;

    }
}
