package me.olivine.ui;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;

import me.olivine.encoder.EncoderUtil;
import me.olivine.sample.R;

public class MainActivity extends AppCompatActivity {

    private static final String TAG = MainActivity.class.getSimpleName();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        byte[] data = EncoderUtil.cryptFromAssets(this, "vertex_shader.sd");
        Log.d(TAG, "after encode:" + new String(data));
        Log.d(TAG, "before encode:" + new String(EncoderUtil.crypt(data)));
    }
}
