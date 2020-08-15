package com.example.stefano.progettomaturita;

import android.support.v7.widget.RecyclerView;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.LinearLayout;
import android.widget.TextView;
import java.util.Vector;

/**
 * Created by stefano on 12/02/16.
 */
public class Adapter_Fermata extends RecyclerView.Adapter<Adapter_Fermata.FermataViewHolder> {

    //rappresenta una classe intermedia tra i dati rappresentati della cardview e la cardview stessa
    public static class FermataViewHolder extends RecyclerView.ViewHolder {

        //elementi del layout che compongono la cradview
        public TextView fermata;
        public TextView localita;
        public TextView ora;
        public LinearLayout layout;

        public String regid;

        //id della fermata rappresentata dall'istanza
        public String fermataID;

        //puntatore alla Activity_Detail che contiene la reclyclerView
        private Activity_Detail parent;

        //riferimento alla viewholder stessa
        private FermataViewHolder thisViewHolder;

        FermataViewHolder(final View itemView, final Activity_Detail parent) {
            super(itemView);
            this.parent=parent;

            //recupero gli elementi del layout
            fermata=(TextView)itemView.findViewById(R.id.nomeFermata);
            localita=(TextView)itemView.findViewById(R.id.nomeLocalita);
            ora=(TextView)itemView.findViewById(R.id.Ora);

            this.regid= Static_Shared_Preferences.GetString(parent,"REGID");

            thisViewHolder=this;

            //recupero il layout "genitore" rispetto alla ViewHolder corrente
            layout=(LinearLayout)itemView.findViewById(R.id.fermataLayout);

            //registro un evento LongClick sul layout parent
            layout.setOnLongClickListener(new View.OnLongClickListener() {
                @Override
                public boolean onLongClick(View v) {

                    //restituisco alla detailActivity la fermata su cui è stato fatto click e il layout corrispondente
                    parent.setCurrentFermata(fermataID);
                    parent.setCurrentFermataView(thisViewHolder);

                    //genero il menù contestuale nel contesto della detailActivity
                    parent.registerForContextMenu(layout);
                    return false;
                }
            });
        }

        //funzione per impostare il colore di sfondo a grigio
        public void setBgColor(){
            layout.setBackgroundColor(parent.getResources().getColor(R.color.gray));
        }

        //funzione per impostare il colore di sfondo a bianco
        public void resetBgColor(){
            layout.setBackgroundColor(parent.getResources().getColor(R.color.white));
        }

    }


    //vettore con tutte le fermate da visualizzare nella recyclerView
    private Vector<Fermata> fermate;

    //vettore che tiene traccia di quali fermate abbiano una notifica registrata
    private Vector<String> notifiche;

    //riferimanto alla detailActivity genitore
    private Activity_Detail parent;

    Adapter_Fermata(Activity_Detail parent, Vector<Fermata> fermate, Vector<String> notifiche ){
        this.fermate = fermate;
        this.parent=parent;
        this.notifiche=notifiche;
    }

    Adapter_Fermata(){
        fermate=new Vector<Fermata>();
    }

    @Override
    public int getItemCount() {
        return fermate.size();
    }

    @Override
    public FermataViewHolder onCreateViewHolder(ViewGroup viewGroup, int i) {
        //recupera il layout e genera gli elementi
        View v = LayoutInflater.from(viewGroup.getContext()).inflate(R.layout.fermata, viewGroup, false);
        FermataViewHolder fvh = new FermataViewHolder(v,parent);
        return fvh;
    }

    @Override
    public void onBindViewHolder(FermataViewHolder fermataViewHolder, int i) {

        //popolo i layout con i dati recuperati in precedenza
        fermataViewHolder.fermata.setText(parent.getString(R.string.fermata)+ fermate.get(i).getNome());
        fermataViewHolder.localita.setText(parent.getString(R.string.loc)+fermate.get(i).getLocalita());
        fermataViewHolder.ora.setText(parent.getString(R.string.ora) + fermate.get(i).getOra());

        //passo l'ID della fermata corrente alla ViewHolder
        fermataViewHolder.fermataID=fermate.get(i).getIDFermata();

        //se su una data fermata è registrata una notifica, allora la coloro di grigio
        if(notifiche.get(i).equals("OK"))
            fermataViewHolder.setBgColor();
        else
            fermataViewHolder.resetBgColor();
    }


}
