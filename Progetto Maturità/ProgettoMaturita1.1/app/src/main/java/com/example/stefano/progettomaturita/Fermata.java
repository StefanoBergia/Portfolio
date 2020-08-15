package com.example.stefano.progettomaturita;

import java.util.StringTokenizer;

/**
 * Created by stefano on 12/02/16.
 */
public class Fermata {

    private String IDFermata;
    private String Nome;
    private String Localita;
    private String ora;
    private String Lat;
    private boolean color;

    public boolean isColor() {
        return color;
    }

    public void setColor(boolean color) {
        this.color = color;
    }


    public String getLon() {
        return Lon;
    }

    public void setLon(String lon) {
        Lon = lon;
    }

    public String getIDFermata() {
        return IDFermata;
    }

    public void setIDFermata(String IDFermata) {
        this.IDFermata = IDFermata;
    }

    public String getNome() {
        return Nome;
    }

    public void setNome(String nome) {
        Nome = nome;
    }

    public String getLocalita() {
        return Localita;
    }

    public void setLocalita(String localita) {
        Localita = localita;
    }

    public String getOra() {
        return ora;
    }

    public void setOra(String ora) {
        this.ora = ora;
    }

    public String getLat() {
        return Lat;
    }

    public void setLat(String lat) {
        Lat = lat;
    }

    private String Lon;

    public Fermata(String IDFermata, String nome, String ora, String localita, String lat, String lon) {
        this.IDFermata = IDFermata;
        this.Nome = nome;
        this.ora = ora;
        this.Localita = localita;
        this.Lat = lat;
        this.Lon = lon;
    }

    public Fermata() {
        this.IDFermata = "";
        this.Nome = "";
        this.ora = "";
        this.Localita = "";
        this.Lat = "";
        this.Lon = "";
        this.color=false;

    }

    public String Serialize(){
      return IDFermata+";"+getNome()+";"+getOra()+";"+getLocalita()+";"+getLat()+";"+getLon();
    }

    public void DeSerialize(String str){
        StringTokenizer st= new StringTokenizer(str,";");
        this.IDFermata = st.nextToken();
        this.Nome = st.nextToken();
        this.ora = st.nextToken();
        this.Localita = st.nextToken();
        this.Lat = st.nextToken();
        this.Lon = st.nextToken();
    }
}
