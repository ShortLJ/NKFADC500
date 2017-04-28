{
	TString lib_MacOS = TString(gSystem -> pwd()) + "/build/libNKFADC500GUI.dylib";
	TString lib_Linux = TString(gSystem -> pwd()) + "/build/libNKFADC500GUI.so";
	if (gSystem -> Load(lib_MacOS) != -1)
		cout << "NKFADC500 system has been successfully loaded." << endl;
	else if (gSystem -> Load(lib_Linux) != -1)
		cout << "NKFADC500 system has been successfully loaded." << endl;
	else
		cout << "Fail to load NKFADC500." << endl;
}
