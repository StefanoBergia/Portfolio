package com.example.stefano.progettomaturita;

import android.content.Context;
import android.widget.ArrayAdapter;
import android.widget.AutoCompleteTextView;
import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;
import java.util.ArrayList;
import java.util.List;

/**
 * Created by User on 04/03/2016.
 */

//recupera i valori da inserire nell'autoCompleteTextView
public class Async_Get_Suggestion extends PostRequest {


    AutoCompleteTextView partenza;
    AutoCompleteTextView arrivo;

    //lista degli elemnti da suggerire
    List<String> lista = null;
    //supporto per l'autocompleteTextView
    String[] Loc;

    Context cx;

    public Async_Get_Suggestion(String url, AutoCompleteTextView partenza, AutoCompleteTextView arrivo, Context cx)
    {
        super(url,null,cx);
        this.partenza=partenza;
        this.arrivo=arrivo;
        this.cx=cx;
    }

    @Override
    protected void onPostExecute(String ret)
    {

        if(!ret.equals("KO") && !ret.equals("NO_INTERNET") ) {

            lista = new ArrayList<String>();
            try {
                JSONObject obj = new JSONObject(ret);
                JSONArray array = null;
                array = obj.getJSONArray("items");
                for (int i = 0; i < array.length(); i++) {
                    JSONObject objJson = array.getJSONObject(i);
                    lista.add(objJson.get("Nome").toString());
                }

            } catch (JSONException jsonEx) {
            }

            Loc = new String[lista.size()];
            for (int i = 0; i < lista.size(); i++) {
                Loc[i] = lista.get(i).toString();
            }
            ArrayAdapter<String> adapter = new ArrayAdapter<String>(cx, android.R.layout.simple_dropdown_item_1line, Loc);
            partenza.setAdapter(adapter);
            arrivo.setAdapter(adapter);

        }
    }


}
