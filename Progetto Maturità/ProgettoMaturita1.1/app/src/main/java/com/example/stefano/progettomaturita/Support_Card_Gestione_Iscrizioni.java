package com.example.stefano.progettomaturita;

/**
 * Created by luca on 5/6/16.
 */
public class Support_Card_Gestione_Iscrizioni extends Support_Card_Linea {

    private String IDFermata;
    private String RagSoc;
    private String nomeFermata;
    private String orario;
    private String tempo;

    public String getRagSoc() {
        return RagSoc;
    }
    public void setRagSoc(String ragSoc) {
        this.RagSoc = ragSoc;
    }

    public String getNomeFermata() {
        return nomeFermata;
    }
    public void setNomeFermata(String nomeFermata){this.nomeFermata = nomeFermata; }

    public String getOrario() {
        return orario;
    }
    public void setOrario(String orario) {this.orario = orario;}

    public String getTempo() {
        return tempo;
    }
    public void setTempo(String tempo) {this.tempo = tempo;}

    public String getIDFermata() { return IDFermata; }

    public void setIDFermata(String IDFermata) {  this.IDFermata = IDFermata; }

    public Support_Card_Gestione_Iscrizioni(){
        super();
        this.RagSoc = "";
        this.nomeFermata = "";
        this.orario = "";
        this.tempo = "";
    }

    public Support_Card_Gestione_Iscrizioni(String IDLinea, String IDOrario, String nomeLinea, String ragSoc, String nomeFermata, String orario, String tempo, String idFermata, Interface_Open_Detail parent) {
        super(IDLinea,IDOrario,nomeLinea,orario,ragSoc,parent);
        this.RagSoc = ragSoc;
        this.nomeFermata = nomeFermata;
        this.orario = orario;
        this.tempo = tempo;
        this.setIDFermata(idFermata);
    }


}
