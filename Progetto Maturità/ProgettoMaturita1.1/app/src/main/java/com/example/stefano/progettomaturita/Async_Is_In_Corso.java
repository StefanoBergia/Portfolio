package com.example.stefano.progettomaturita;
;
import android.support.v7.widget.CardView;
import android.view.View;

/**
 * Created by stefano on 07/04/16.
 */
public class Async_Is_In_Corso extends PostRequest
{
    private CardView cv;

    public Async_Is_In_Corso(String url, Dictionary data, CardView cv) {
        super(url,data,cv.getContext());
        this.cv = cv;

    }

    @Override
    protected void onPostExecute(String s) {
        super.onPostExecute(s);
        if(s.equals("OK"))
        {
            //se la linea è in corso coloro la Cardview di grigio in modo da notificarli all'utente
            cv.setCardBackgroundColor(cv.getContext().getResources().getColor(R.color.gray));
            cv.findViewById(R.id.warning).setVisibility(View.VISIBLE);
        }
    }
}


