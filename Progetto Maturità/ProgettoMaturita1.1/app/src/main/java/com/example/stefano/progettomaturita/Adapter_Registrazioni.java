package com.example.stefano.progettomaturita;

import android.support.v7.widget.CardView;
import android.support.v7.widget.RecyclerView;
import android.text.Html;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.LinearLayout;
import android.widget.TextView;

import java.util.Vector;

/**
 * Created by luca on 5/6/16.
 */
public class Adapter_Registrazioni extends RecyclerView.Adapter<Adapter_Registrazioni.IscrizioneViewHolder>{

    //rappresenta una classe intermedia tra i dati rappresentati della cardview e la cardview stessa
    public static class IscrizioneViewHolder extends RecyclerView.ViewHolder {

        //elementi del layout che compongono la cardview
        public CardView cv;
        public TextView NomeLinea;
        public TextView NomeFermata;
        public TextView Ora;
        public TextView Ditta;
        public TextView Ritardo;
        public LinearLayout layout;

        //informazioni da visualizzare
        public Support_Card_Gestione_Iscrizioni IscrObj;
        public String IDOrario;
        public String IDFermata;
        public String ritardo;


        private Activity_Gestione_Notifiche parent;


        IscrizioneViewHolder(View itemView, final Activity_Gestione_Notifiche parent) {
            super(itemView);
            this.parent = parent;

            //recupero gli elementi del layout
            cv = (CardView)itemView.findViewById(R.id.cvNotifiche);
            NomeLinea = (TextView)itemView.findViewById(R.id.txtLinea);
            Ora = (TextView)itemView.findViewById(R.id.txtOra);
            Ditta = (TextView)itemView.findViewById(R.id.txtDitta);
            NomeFermata = (TextView)itemView.findViewById(R.id.txtFermata);
            Ritardo = (TextView)itemView.findViewById(R.id.txtRitardo);
            layout=(LinearLayout)itemView.findViewById(R.id.layoutNotifica);

            //registro un evento click sulla cardview
            layout.setOnClickListener(new View.OnClickListener() {
                @Override
                public void onClick(View v) {
                    //apro la detailActivity associata alla linea corrente
                    IscrObj.getParent().OpenDetail(IscrObj);
                }
            });

            //registro un evento LongClick sul layout parent
            layout.setOnLongClickListener(new View.OnLongClickListener() {
                @Override
                public boolean onLongClick(View v) {

                    //restituisco all'Activity le informazioni riguardanti la notifica su cui è stato fatto click
                    parent.setParametri(IDOrario, IDFermata, ritardo);

                    // apro il menu contestuale
                    parent.registerForContextMenu(layout);

                    return false;
                }
            });
        }

        //metodo per recuperare l'oggetto cardview
        public CardView GetCardView()
        {
            return  cv;
        }

    }

    private Activity_Gestione_Notifiche parent;

    private Vector<Support_Card_Gestione_Iscrizioni> iscrizioni;

    public void addLinea(Support_Card_Gestione_Iscrizioni cd){
        iscrizioni.add(cd);
    }

    public void removeLinea(int pos){
        iscrizioni.remove(pos);
    }

    Adapter_Registrazioni(Vector<Support_Card_Gestione_Iscrizioni> linee, Activity_Gestione_Notifiche parent){
        this.iscrizioni = linee;
        this.parent = parent;
    }

    Adapter_Registrazioni(){
        iscrizioni=new Vector<Support_Card_Gestione_Iscrizioni>();
    }

    @Override
    public int getItemCount() {
        return iscrizioni.size();
    }

    @Override
    public IscrizioneViewHolder onCreateViewHolder(ViewGroup viewGroup, int i) {
        //recupera il layout e genera gli elementi
        View v = LayoutInflater.from(viewGroup.getContext()).inflate(R.layout.notifiche_item, viewGroup, false);
        IscrizioneViewHolder ivh = new IscrizioneViewHolder(v, parent);
        return ivh;
    }

    @Override
    public void onBindViewHolder(IscrizioneViewHolder ivh, int i) {

        //popolo i layout con i dati recuperati in precedenza
        ivh.NomeLinea.setText( parent.getString(R.string.nome_linea)+ iscrizioni.get(i).getNomeLinea());
        ivh.NomeFermata.setText( parent.getString(R.string.nome_fermata)+ iscrizioni.get(i).getNomeFermata());
        ivh.Ora.setText( parent.getString(R.string.ora_passaggio)+ iscrizioni.get(i).getOrario());
        ivh.Ditta.setText(parent.getString(R.string.nome_ditta)+iscrizioni.get(i).getRagSoc());
        ivh.Ritardo.setText(Html.fromHtml(String.format(parent.getString(R.string.msg_notifica), iscrizioni.get(i).getTempo())));
        ivh.IscrObj = iscrizioni.get(i);

        //passo le informazioni riguardanti la notifica al viewholder
        ivh.IDOrario = iscrizioni.get(i).getIDOrario();
        ivh.IDFermata = iscrizioni.get(i).getIDFermata();
        ivh.ritardo = iscrizioni.get(i).getTempo();

        Dictionary data=new Dictionary();
        data.AddItem("IDOrario",iscrizioni.get(i).getIDOrario());
        new Async_Is_In_Corso(parent.getString(R.string.is_in_corso),data,ivh.GetCardView()).execute();
    }
}
