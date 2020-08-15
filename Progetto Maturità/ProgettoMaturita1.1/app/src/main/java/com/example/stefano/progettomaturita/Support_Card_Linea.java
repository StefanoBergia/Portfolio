package com.example.stefano.progettomaturita;

import java.util.StringTokenizer;



//rappresenta le informazioni riguardanti le linee visualizzate nelle cardview
public class Support_Card_Linea {

    private String IDLinea;
    private String IDOrario;
    private String NomeLinea;
    private String Ora;
    private String Ditta;
    private Interface_Open_Detail parent;


    public Interface_Open_Detail getParent() { return parent;}

    public void setParent(Interface_Open_Detail parent) {this.parent = parent;}

    public String getIDLinea() {
        return IDLinea;
    }

    public void setIDLinea(String IDLinea) {
        this.IDLinea = IDLinea;
    }

    public String getIDOrario() {
        return IDOrario;
    }

    public void setIDOrario(String IDOrario) {
        this.IDOrario = IDOrario;
    }

    public String getNomeLinea() {
        return NomeLinea;
    }

    public void setNomeLinea(String nomeLinea) {
        NomeLinea = nomeLinea;
    }

    public String getOra() {
        return Ora;
    }

    public void setOra(String ora) {
        Ora = ora;
    }

    public String getDitta() {
        return Ditta;
    }

    public void setDitta(String ditta) {
        Ditta = ditta;
    }

    public Support_Card_Linea() {
        this.IDLinea = "";

        this.IDOrario = "";
        NomeLinea = "";
        Ora = "";
        Ditta = "";

    }

    public Support_Card_Linea(String IDLinea, String IDOrario, String nomeLinea, String ora, String ditta, Interface_Open_Detail parent) {
        this.IDLinea = IDLinea;
        this.IDOrario = IDOrario;
        NomeLinea = nomeLinea;
        Ora = ora;
        Ditta = ditta;
        this.parent=parent;

    }

    public void DeSerialize(String s,Interface_Open_Detail parent){
        StringTokenizer st=new StringTokenizer(s,";");
        this.IDOrario=st.nextToken();
        this.Ditta=st.nextToken();
        this.IDLinea=st.nextToken();
        this.Ora=st.nextToken();
        this.NomeLinea=st.nextToken();
        this.parent=parent;
    }
}