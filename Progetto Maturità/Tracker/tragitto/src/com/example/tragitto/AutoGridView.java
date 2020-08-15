package com.example.tragitto;

import android.content.Context;
import android.content.res.Configuration;
import android.util.AttributeSet;
import android.util.Log;
import android.view.View;
import android.widget.GridView;
import android.widget.ListAdapter;

/**
 * Automatically calculates the ideal for each row
 * @author JJ
 *
 */
public class AutoGridView extends GridView {

    private static final String TAG = "AutoGridView";
    private int numColumnsID;
    private int previousFirstVisible;
    private int numColumns = 1;
    private boolean allTheSame;

    public boolean GetAllTheSame(){
        return allTheSame;
    }

    public void SetAllTheSame(boolean val){
        allTheSame=val;
        setHeights();
    }


    public AutoGridView(Context context, AttributeSet attrs, int defStyle) {
        super(context, attrs, defStyle);
        allTheSame=false;
        init(attrs);
    }

    public AutoGridView(Context context, AttributeSet attrs) {
        super(context, attrs);
        allTheSame=false;
        init(attrs);
    }

    public AutoGridView(Context context) {
        super(context);
        allTheSame=false;
    }

    /**
     * Sets the numColumns based on the attributeset
     */
    private void init(AttributeSet attrs) {
    // Read numColumns out of the AttributeSet
        int count = attrs.getAttributeCount();
        if(count > 0) {
            for(int i = 0; i < count; i++) {
                String name = attrs.getAttributeName(i);
                if(name != null && name.equals("numColumns")) {
                    // Update columns
                    this.numColumnsID = attrs.getAttributeResourceValue(i, 1);
                     updateColumns();
                    break;
                }
            }
        }
        Log.d(TAG, "numColumns set to: " + numColumns);
    }

    /** * Reads the amount of columns from the resource file and * updates the "numColumns" variable */
    private void updateColumns() {
        this.numColumns = getContext().getResources().getInteger(numColumnsID);
    }

    /*This method has been overridden to grab the new value of the number of columns,
    and to adjust the selection. The selection needs to be adjusted so the same row
    is shown to the user before a rotation.*/
    @Override public void setNumColumns(int numColumns) {
        this.numColumns = numColumns;
        super.setNumColumns(numColumns);
        Log.d(TAG, "setSelection --> " + previousFirstVisible);
        setSelection(previousFirstVisible);
     }


    /*
    This method has been overridden to calculate the new heights of the views.
    * */
    @Override
    protected void onLayout(boolean changed, int leftPos, int topPos, int rightPos, int bottomPos) {
        super.onLayout(changed, leftPos, topPos, rightPos, bottomPos);
        setHeights();
    }


    /*
    This method has been overridden to update the amount of columns to show.
    */
    @Override
    protected void onConfigurationChanged(Configuration newConfig) {
        updateColumns();
        setNumColumns(this.numColumns);
    }


    /*
    This method has been overridden to check if new views need to be shown.
    If this is the case, the view heights must be recalculated.
    **/
    @Override
    protected void onScrollChanged(int newHorizontal, int newVertical, int oldHorizontal, int oldVertical) {
// Check if the first visible position has changed due to this scroll
        int firstVisible = getFirstVisiblePosition();
        if(previousFirstVisible != firstVisible) {
// Update position, and update heights
            previousFirstVisible = firstVisible;
            setHeights();
        }

        super.onScrollChanged(newHorizontal, newVertical, oldHorizontal, oldVertical);
    }

/**
 * Sets the height of each view in a row equal to the height of the tallest view in this row
 *
 *
 * This is the method where all the magic happens.
 * The used adapter gets retrieved, and by using this adapter we can get the displayed views.
 * With the help of the numColumns variable the views per row can be determined.
 * The tallest height gets calculated, and is then applied to each view.
 */
    private void setHeights() {
        ListAdapter adapter = getAdapter();

        if(adapter != null) {
            if(!allTheSame)
            {
                for(int i = 0; i < getChildCount(); i+=numColumns) {
                    // Determine the maximum height for this row
                    int maxHeight = 0;
                    for(int j = i; j < i+numColumns; j++)
                    {
                        View view = getChildAt(j);
                        if(view != null && view.getHeight() > maxHeight) {
                            maxHeight = view.getHeight();
                        }
                    }
                    // Set max height for each element in this row
                    if(maxHeight > 0) {
                        for(int j = i; j < i+numColumns; j++) {
                            View view = getChildAt(j);
                            if(view != null && view.getHeight() != maxHeight) {
                                view.setMinimumHeight(maxHeight);
                            }
                        }
                    }
                }
            }else {
                int maxHeight = 0;
                for (int j = 0; j < getChildCount(); j++) {
                    View view = getChildAt(j);
                    if (view != null && view.getHeight() > maxHeight) {
                        maxHeight = view.getHeight();
                    }
                }
                for (int i = 0; i < getChildCount(); i++) {
                    if (maxHeight > 0) {
                        View view = getChildAt(i);
                        if (view != null && view.getHeight() != maxHeight) {
                            view.setMinimumHeight(maxHeight);
                        }
                    }
                }
            }
        }
    }
}
