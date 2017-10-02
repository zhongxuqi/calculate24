/****************************************************************************
Copyright (c) 2015-2017 Chukong Technologies Inc.
 
http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
package org.cocos2dx.cpp;

import android.app.AlertDialog;
import android.content.Context;
import android.content.DialogInterface;
import android.content.SharedPreferences;
import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;
import android.os.Bundle;
import android.os.Handler;
import android.util.Log;

import com.musketeer.calculate24.R;

import org.cocos2dx.lib.Cocos2dxActivity;
import org.cocos2dx.lib.Cocos2dxHandler;

public class AppActivity extends Cocos2dxActivity implements SensorEventListener {
    private static final String TAG = "AppActivity";

    protected static SharedPreferences sharedPreferences = null;
    protected static AppActivity activity = null;
    protected static Handler handler;
    protected static Cocos2dxHandler cocos2dxHandler;

    protected SensorManager mSensorManager = null;
    protected Sensor mSensor = null;
    protected AlertDialog dialog;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        this.mSensorManager = (SensorManager) getSystemService(Context.SENSOR_SERVICE);
        this.mSensor = mSensorManager.getDefaultSensor(Sensor.TYPE_GRAVITY);

        sharedPreferences = getSharedPreferences("calculate24", Context.MODE_PRIVATE);
        activity = this;
        handler = new Handler();
        cocos2dxHandler = new Cocos2dxHandler(this);
    }

    @Override
    protected void onResume() {
        super.onResume();
        mSensorManager.registerListener(this, this.mSensor, SensorManager.SENSOR_DELAY_GAME);
    }

    @Override
    protected void onPause() {
        super.onPause();
        mSensorManager.unregisterListener(this);
    }

    @Override
    public void onSensorChanged(SensorEvent event) {
        PushSensorInfo(event.values[0], event.values[1]);
    }

    @Override
    public void onAccuracyChanged(Sensor sensor, int i) {

    }

    protected native void PushSensorInfo(float forceX, float forceY);

    public static void PutStringPref(String key, String value) {
        if (sharedPreferences == null) {
            return;
        }
        sharedPreferences.edit().putString(key, value).apply();
    }

    public static String GetStringPref(String key) {
        if (sharedPreferences == null) {
            return "";
        }
        return sharedPreferences.getString(key, "");
    }

    public static void PutIntPref(String key, int value) {
        if (sharedPreferences == null) {
            return;
        }
        sharedPreferences.edit().putInt(key, value).apply();
    }

    public static int GetIntPref(String key) {
        if (sharedPreferences == null) {
            return 0;
        }
        return sharedPreferences.getInt(key, 0);
    }

    public static void PutBoolPref(String key, boolean value) {
        if (sharedPreferences == null) {
            return;
        }
        sharedPreferences.edit().putBoolean(key, value).apply();
    }

    public static boolean GetBoolPref(String key) {
        if (sharedPreferences == null) {
            return false;
        }
        return sharedPreferences.getBoolean(key, false);
    }

    protected native void QuitGame();
    public static void AlertQuitGame() {
        if (handler == null) {
            return;
        }
        handler.post(new Runnable() {
            @Override
            public void run() {
                final AppActivity activity = AppActivity.activity;
                if (activity == null) {
                    return;
                }
                if (activity.dialog != null) {
                    activity.dialog.dismiss();
                }
                AlertDialog.Builder builder = new AlertDialog.Builder(activity);
                builder.setMessage(activity.getString(R.string.quit_alert));
                builder.setNegativeButton(R.string.cancel, new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialogInterface, int i) {
                        if (activity.dialog != null) {
                            activity.dialog.dismiss();
                        }
                    }
                });
                builder.setPositiveButton(R.string.quit_game, new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialogInterface, int i) {
                        if (activity.dialog != null) {
                            activity.dialog.dismiss();
                        }
                        activity.QuitGame();
                    }
                });
                activity.dialog = builder.create();
                activity.dialog.show();
            }
        });
    }

    protected native void NewGame();
    protected native void ResumeGame();
    public static void AlertResumeGame() {
        if (handler == null) {
            return;
        }
        handler.post(new Runnable() {
            @Override
            public void run() {
                final AppActivity activity = AppActivity.activity;
                if (activity == null) {
                    return;
                }
                if (activity.dialog != null) {
                    activity.dialog.dismiss();
                }
                AlertDialog.Builder builder = new AlertDialog.Builder(activity);
                builder.setMessage(activity.getString(R.string.resume_alert));
                builder.setNegativeButton(R.string.new_game, new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialogInterface, int i) {
                        if (activity.dialog != null) {
                            activity.dialog.dismiss();
                        }
                        activity.NewGame();
                    }
                });
                builder.setPositiveButton(R.string.resume_game, new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialogInterface, int i) {
                        if (activity.dialog != null) {
                            activity.dialog.dismiss();
                        }
                        activity.ResumeGame();
                    }
                });
                builder.setCancelable(false);
                activity.dialog = builder.create();
                activity.dialog.show();
            }
        });
    }

    protected native void QuitAPP();
    public static void AlertQuitAPP() {
        if (handler == null) {
            return;
        }
        handler.post(new Runnable() {
            @Override
            public void run() {
                final AppActivity activity = AppActivity.activity;
                if (activity == null) {
                    return;
                }
                if (activity.dialog != null) {
                    activity.dialog.dismiss();
                }
                AlertDialog.Builder builder = new AlertDialog.Builder(activity);
                builder.setMessage(activity.getString(R.string.quit_app_alert));
                builder.setNegativeButton(R.string.cancel, new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialogInterface, int i) {
                        if (activity.dialog != null) {
                            activity.dialog.dismiss();
                        }
                    }
                });
                builder.setPositiveButton(R.string.quit, new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialogInterface, int i) {
                        if (activity.dialog != null) {
                            activity.dialog.dismiss();
                        }
                        activity.QuitAPP();
                    }
                });
                activity.dialog = builder.create();
                activity.dialog.show();
            }
        });
    }
}
