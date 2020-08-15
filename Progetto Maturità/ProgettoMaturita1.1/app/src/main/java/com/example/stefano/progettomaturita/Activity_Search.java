package com.example.stefano.progettomaturita;

import android.content.Context;
import android.content.Intent;
import android.graphics.drawable.ColorDrawable;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.RecyclerView;
import android.support.v7.widget.Toolbar;
import android.view.KeyEvent;
import android.view.Menu;
import android.view.MenuItem;
import android.view.inputmethod.EditorInfo;
import android.view.inputmethod.InputMethodManager;
import android.widget.AutoCompleteTextView;
import android.widget.TextView;

public class Activity_Search extends AppCompatActivity implements Interface_Open_Detail {

    public TextView lblMsg;
    public RecyclerView rv;
    public AutoCompleteTextView txtPartenza;
    public AutoCompleteTextView txtArrivo;
    private Context cx;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_search);
        Toolbar toolbar = (Toolbar) findViewById(R.id.toolbar);
        setSupportActionBar(toolbar);
        getSupportActionBar().setDisplayHomeAsUpEnabled(true);

        //recupero i componenti del layout
        txtPartenza=(AutoCompleteTextView)findViewById(R.id.departureTxt);
        txtArrivo=(AutoCompleteTextView)findViewById(R.id.arrivalTxt);
        lblMsg=(TextView)findViewById(R.id.lblMsg);
        rv = (RecyclerView)findViewById(R.id.recycler);
        rv.setHasFixedSize(true);

        //imposto il colore di sfondo per le textBox
        txtArrivo.setDropDownBackgroundDrawable(new ColorDrawable(this.getResources().getColor(R.color.autoCompleteTextView)));
        txtPartenza.setDropDownBackgroundDrawable(new ColorDrawable(this.getResources().getColor(R.color.autoCompleteTextView)));

        //inizializzo le caselle di ricerca con tutti i suggerimenti possibili
        new Async_Get_Suggestion(getString(R.string.get_hints),txtPartenza,txtArrivo,this).execute();

        txtPartenza.setOnEditorActionListener(new AutoCompleteTextView.OnEditorActionListener() {
            @Override
            public boolean onEditorAction(TextView v, int actionId, KeyEvent event) {
            try {
                //se viene premuto invio con il focus sulla prima casella di inseriemento, il focus viene spostato sulla seconda
                if (actionId == EditorInfo.IME_ACTION_NEXT) {
                    txtPartenza.clearFocus();
                    txtArrivo.requestFocus();
                    return true;
                } else {
                    return false;
                }
            } catch (Exception e) {
                return false;
            }
            }

        });

        txtArrivo.setOnEditorActionListener(new AutoCompleteTextView.OnEditorActionListener() {
            @Override
            public boolean onEditorAction(TextView v, int actionId, KeyEvent event) {
            try {
                // se si preme invio con il focus sulla seconda casella, viene avviata la ricerca
                if (actionId == EditorInfo.IME_ACTION_NEXT) {
                    //avvio la ricerca
                    StartSearch();
                    return true;
                } else {
                    return false;
                }
            } catch (Exception e) {
                return false;
            }
            }
        });
    }

    //metodo per avviare la ricerca
    public void StartSearch(){
        //nascondo la tastiera eventualmente aperta
        InputMethodManager imm = (InputMethodManager) getSystemService(Context.INPUT_METHOD_SERVICE);
        imm.toggleSoftInput(InputMethodManager.SHOW_FORCED, 0);

        //se entrambi i campi sono completati avvio la ricerca
        if (!txtArrivo.getText().toString().equals("") && !txtPartenza.getText().toString().equals("")) {

            Dictionary data= new Dictionary();
            data.AddItem("Partenza",txtPartenza.getText().toString());
            data.AddItem("Arrivo",txtArrivo.getText().toString());
            new Async_Get_Linee(getString(R.string.search_lines),data,this, rv, lblMsg).execute();

            //pulisco le caselle di testo
            txtPartenza.setText("");
            txtArrivo.setText("");

        } else
            lblMsg.setText(getString(R.string.lblMsg));
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        getMenuInflater().inflate(R.menu.mainsearch, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {

        switch (item.getItemId())
        {
            case R.id.action_search:
                StartSearch();
                break;
            case R.id.action_swap:
                String supp=txtArrivo.getText().toString();
                txtArrivo.setText(txtPartenza.getText().toString());
                txtPartenza.setText(supp);
                break;
            case R.id.home:
                Intent intent=new Intent(Activity_Search.this,Activity_Main.class);
                startActivity(intent);
                break;
            default:
                Static_Shared_Menu.OptionItemSelected(item,this,getString(R.string.search_guide));
        }

        return super.onOptionsItemSelected(item);
    }

    @Override
    public void onBackPressed() {
        super.onBackPressed();
        Intent intent=new Intent(Activity_Search.this,Activity_Main.class);
        startActivity(intent);
    }

    public void OpenDetail(Support_Card_Linea Linea){

        Intent intent = new Intent(Activity_Search.this,Activity_Detail.class);
        intent.putExtra("IDOrario",Linea.getIDOrario());
        intent.putExtra("Ditta",Linea.getDitta());
        intent.putExtra("IDLinea",Linea.getIDLinea());
        intent.putExtra("Ora",Linea.getOra());
        intent.putExtra("NomeLinea",Linea.getNomeLinea());
        intent.putExtra("Back",2);
        startActivity(intent);
    }

}
