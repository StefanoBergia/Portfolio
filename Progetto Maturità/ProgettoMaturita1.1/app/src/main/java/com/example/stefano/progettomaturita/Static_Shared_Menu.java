package com.example.stefano.progettomaturita;

import android.app.Activity;
import android.app.AlertDialog;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.support.design.widget.Snackbar;
import android.text.Html;
import android.view.MenuItem;

/**
 * Created by stefano on 25/07/16.
 */
public class Static_Shared_Menu {

    //serve per evitare di ricopiare in ogni activity le voci del menu che si ripetono
    public static boolean OptionItemSelected(MenuItem item, Context cx, String guideMsg )
    {
        int id = item.getItemId();

        switch (id){
            case R.id.action_search:
                if(Static_Connection_Checker.Check(cx)) {
                    Intent intent = new Intent(cx, Activity_Search.class);
                    cx.startActivity(intent);
                } else
                {
                    //Snackbar snack = Snackbar.make(((Activity)cx).findViewById(android.R.id.content), cx.getString(R.string.no_internet_2), Snackbar.LENGTH_LONG);
                    //snack.show();
                }
                return true;

            case R.id.action_guide:
                new AlertDialog.Builder(cx)
                        .setTitle(cx.getString(R.string.guide))
                        .setMessage(Html.fromHtml(guideMsg))
                        .setPositiveButton(android.R.string.ok, new DialogInterface.OnClickListener() {
                            public void onClick(DialogInterface dialog, int which) {
                                // continue with delete
                            }
                        })
                        .setIcon(R.drawable.nautibus_icon_192)
                        .show();
                break;
            case R.id.action_about:
                new AlertDialog.Builder(cx)
                        .setTitle(cx.getString(R.string.app_name))
                        .setMessage(Html.fromHtml(cx.getString(R.string.about)))
                        .setPositiveButton(android.R.string.ok, new DialogInterface.OnClickListener() {
                            public void onClick(DialogInterface dialog, int which) {
                                // continue with delete
                            }
                        })
                        .setIcon(R.drawable.nautibus_icon_192)
                        .show();
                break;
        }

        return true;
    }
}
