package com.example.stefano.progettomaturita;

import android.content.Context;
import android.support.v7.widget.CardView;
import android.support.v7.widget.RecyclerView;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;
import java.util.Vector;

/**
 * Created by stefano on 05/02/16.
 */

public class Adpater_Linee extends RecyclerView.Adapter<Adpater_Linee.LineaViewHolder>{

    //rappresenta una classe intermedia tra i dati rappresentati della cardview e la cardview stessa
    public static class LineaViewHolder extends RecyclerView.ViewHolder {

        //elementi del layout che compongono la cardview
        public CardView cv;
        public TextView NomeLinea;
        public TextView  Ora;
        public TextView Ditta;
        public Support_Card_Linea LineaObj;


        LineaViewHolder(View itemView) {
            super(itemView);

            //recupero gli elementi del layout
            cv = (CardView)itemView.findViewById(R.id.cv);
            NomeLinea = (TextView)itemView.findViewById(R.id.txtLinea);
            Ora = (TextView)itemView.findViewById(R.id.txtOra);
            Ditta = (TextView)itemView.findViewById(R.id.txtDitta);

            //registro un evento click sulla cardview
            cv.setOnClickListener(new View.OnClickListener() {
                @Override
                public void onClick(View v) {
                //apro la detailActivity associata alla linea corrente
                LineaObj.getParent().OpenDetail(LineaObj);
                }
            });
        }

        //metodo per recuperare l'oggetto cardview
        public CardView GetcardView()
        {
            return  cv;
        }
    }

    //vettore contenete le linee da visualizzare nella cardview
    private Vector<Support_Card_Linea> linee;

    private Context cx;

    Adpater_Linee(Vector<Support_Card_Linea> linee, Context cx){
        this.linee = linee;
        this.cx=cx;
    }

    @Override
    public int getItemCount() {
        return linee.size();
    }

    @Override
    public LineaViewHolder onCreateViewHolder(ViewGroup viewGroup, int i) {
        //recupera il layout e genera gli elementi
        View v = LayoutInflater.from(viewGroup.getContext()).inflate(R.layout.linee_item, viewGroup, false);
        LineaViewHolder lvh = new LineaViewHolder(v);
        return lvh;
    }

    @Override
    public void onBindViewHolder(LineaViewHolder lineaViewHolder, int i) {

        //popolo i layout con i dati recuperati in precedenza
        lineaViewHolder.NomeLinea.setText(cx.getString(R.string.nome_linea)+linee.get(i).getNomeLinea());
        lineaViewHolder.Ora.setText(cx.getString(R.string.ora_partenza)+linee.get(i).getOra());
        lineaViewHolder.Ditta.setText(cx.getString(R.string.nome_ditta)+linee.get(i).getDitta());

        //aggiungo all'oggetto lineaViewholder un riferimento all'oggetto CardView corrente in modo da poter aprire l'activity del dettaglio
        lineaViewHolder.LineaObj=linee.get(i);

        //verifico se la linea è in corso per poter colorare la cardview di grigio mostrando così l'avviso
        Dictionary data=new Dictionary();
        data.AddItem("IDOrario",linee.get(i).getIDOrario());
        new Async_Is_In_Corso(cx.getString(R.string.is_in_corso),data,lineaViewHolder.GetcardView()).execute();

    }
}
