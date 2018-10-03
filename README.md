# CE-4302-TallerOpenMP_NEON
 Para compilar se debe modificar los archivos:
+ Android.mk
+ Application.mk

Para indicar cual es el programa que se va a compilar.

	Ejecutar los siguientes comandos:
	
	/opt/android-ndk-r16b/ndk-build

	adb push ../libs/armeabi-v7a/<nombre> /data/local/tmp

	adb shell /data/local/tmp/<nombre>
