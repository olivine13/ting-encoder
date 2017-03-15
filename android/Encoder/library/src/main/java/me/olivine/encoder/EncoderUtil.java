package me.olivine.encoder;

import android.content.Context;
import android.support.annotation.Keep;
import android.util.Log;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStream;

/**
 * TODO Description
 *
 * @author laizhenqi
 * @since 2017/3/3
 */

public class EncoderUtil {

    private final static String TAG = EncoderUtil.class.getSimpleName();

    static {
        System.loadLibrary("encoder");
    }

    private static final int BUFFER_SIZE = 1024;

    public static byte[] crypt(byte[] src) {
        return nativeCrypt(src);
    }

    public static byte[] cryptFromLocal(String path) {
        FileInputStream fis = null;
        byte[] data = null;
        try {
            fis = new FileInputStream(new File(path));
            data = readFromInputStream(fis);
        } catch (FileNotFoundException e) {
            Log.e(TAG, "file " + path + " not found");
        } catch (IOException e) {
            Log.e(TAG, "file " + path + " read failed");
        } finally {
            if (fis != null) try {
                fis.close();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
        if (data == null) {
            return null;
        }
        return nativeCrypt(data);
    }

    public static byte[] cryptFromAssets(Context context, String path) {
        InputStream is = null;
        byte[] data = null;
        try {
            is = context.getAssets().open(path);
            data = readFromInputStream(is);
        } catch (IOException e) {
            e.printStackTrace();
        } finally {
            if (is != null) try {
                is.close();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
        if (data == null) {
            return null;
        }
        return nativeCrypt(data);
    }

    public static byte[] readFromInputStream(InputStream is) throws IOException {
        byte[] data = new byte[BUFFER_SIZE];
        byte[] buffer = new byte[BUFFER_SIZE];
        int r = 0;
        int sum = 0;
        int offset = 0;
        while ((r = is.read(buffer)) > 0) {
            sum += r;
            //如果带存储字节数大于最大容量，则对data数组进行扩容
            if (sum > BUFFER_SIZE) {
                byte[] tmp = new byte[(sum / BUFFER_SIZE + 1) * BUFFER_SIZE];
                System.arraycopy(data, 0, tmp, 0, data.length);
                data = tmp;
            }
            //将buffer中的r个字节拷贝到data从offset开始的位置
            System.arraycopy(buffer, 0, data, offset, r);
            offset += r;
        }
        //获取到的实际大小数组
        byte[] tmp = new byte[sum];
        System.arraycopy(data, 0, tmp, 0, sum);
        return tmp;
    }

    @Keep
    private static native byte[] nativeCrypt(byte[] src);
}
