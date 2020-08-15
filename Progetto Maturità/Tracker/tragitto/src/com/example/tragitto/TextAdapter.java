package com.example.tragitto;

import android.content.Context;
import android.graphics.Color;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseAdapter;
import android.widget.GridView;
import android.widget.TextView;

import java.util.Vector;

public class TextAdapter extends BaseAdapter {

    private Context mContext;
    public TextAdapter(Context c) {
        mContext = c;
        textToShow=new Vector<String>();
    }

    private Vector<String> textToShow;

    public int getCount() {
        return textToShow.size();
    }
    public void AddItem(String ns){
        textToShow.add(ns);
    }
    public String getItem(int position) {
        return textToShow.elementAt(position);
    }
    public void RemoveElement(int position){
        textToShow.removeElementAt(position);
    }

    public long getItemId(int position) {
        return 0;
    }

    public View getView(int position, View convertView, ViewGroup parent) {
        TextView textView;
        if (convertView == null) {
            textView = new TextView(mContext);
           textView.setLayoutParams(new GridView.LayoutParams( ViewGroup.LayoutParams.MATCH_PARENT,100));
            textView.setPadding(20, 8, 20, 8);
        } else {
            textView = (TextView) convertView;
        }

        textView.setText(textToShow.elementAt(position));

        //////////////////////////////////////////////
        textView.setBackgroundColor(Color.DKGRAY);
        textView.setTextColor(Color.WHITE);
        /////////////////////////////////////////////

        return textView;
    }
}

/*
TextAdapter txtView=new TextAdapter(this);
        String supp;
        for(int i=0;i<txt.size();i++)
        {
            txtView.AddItem("Mittente:"+txt.elementAt(i).getFrom());
            txtView.AddItem("Destinatario:"+txt.elementAt(i).getTo());
            txtView.AddItem("Testo:\t"+txt.elementAt(i).getBody());
        }
        GridView grid=(GridView)findViewById(R.id.grid);
        grid.setAdapter(txtView);
*/
