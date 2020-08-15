package com.example.stefano.progettomaturita;

import android.app.Notification;
import android.app.NotificationManager;
import android.app.PendingIntent;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.media.RingtoneManager;
import android.net.Uri;
import android.os.Bundle;
import android.support.v4.app.NotificationCompat;
import com.google.android.gms.gcm.GoogleCloudMessaging;

/**
 * Created by stefano on 08/04/16.
 */
public class NotificationReceiver extends BroadcastReceiver {

    private NotificationManager mNotificationManager;
    private String fileNotifiche;

    public NotificationReceiver() {
        super();
    }

    @Override
    public void onReceive(Context context, Intent intent) {
        GoogleCloudMessaging gcm = GoogleCloudMessaging.getInstance(context);
        Bundle extras = intent.getExtras();

        String messageType = gcm.getMessageType(intent);

        if (!extras.isEmpty())
        {
            if (GoogleCloudMessaging.MESSAGE_TYPE_MESSAGE.equals(messageType))
            {
                // emette una notifica sul dispositivo
                sendNotification(context, extras);
            }
        }

    }

    private void sendNotification(Context ctx,Bundle data)
    {
        //modifica
        mNotificationManager = (NotificationManager) ctx.getSystemService(Context.NOTIFICATION_SERVICE);
        int requestID = (int)System.currentTimeMillis();
        // scelta suoneria per notifica
        Uri sound = RingtoneManager.getDefaultUri(RingtoneManager.TYPE_NOTIFICATION);
        String msg=ctx.getString(R.string.init) +" "+ data.getString("Fermata") +" "+ ctx.getString(R.string.mid)+ " "+data.getString("Tempo") +" "+ ctx.getString(R.string.end);
        NotificationCompat.Builder mBuilder =
                new NotificationCompat.Builder(ctx)
                        .setSmallIcon(R.drawable.nautibus_icon_192)
                        .setContentTitle(data.getString("NomeLinea"))
                        .setContentText(msg)
                        .setSound(sound)
                        .setStyle(new NotificationCompat.BigTextStyle()
                                .bigText(msg));



        Intent Nintent = new Intent(ctx, Activity_Detail.class);
        Nintent.putExtra("IDOrario",data.getString("IDOrario"));
        Nintent.putExtra("Ditta",data.getString("Ditta"));
        Nintent.putExtra("IDLinea",data.getString("IDLinea"));
        Nintent.putExtra("Ora",data.getString("Ora"));
        Nintent.putExtra("NomeLinea",data.getString("NomeLinea"));
        Nintent.putExtra("RegID", data.getString("RegID"));
        Nintent.putExtra("IDFermata",data.getString("IDFermata"));
        Nintent.putExtra("Back",1);

        Nintent.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK );

        PendingIntent intent = PendingIntent.getActivity(ctx, 1,
                Nintent, PendingIntent.FLAG_UPDATE_CURRENT);

        mBuilder.setContentIntent(intent);

        Notification notification = mBuilder.build();

        notification.flags |= Notification.FLAG_AUTO_CANCEL;

        // effettua la notifica
        mNotificationManager.notify(requestID, notification);

        fileNotifiche=ctx.getFilesDir()+"/"+ctx.getString(R.string.saved_n);
        Static_Gestione_File.RemoveFromFile(fileNotifiche,data.getString("IDOrario") + ";" + data.getString("IDFermata"));

    }

}
