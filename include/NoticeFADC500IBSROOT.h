#ifndef NKFADC500IBS_ROOT_H
#define NKFADC500IBS_ROOT_H

#include "TObject.h"

struct libusb_context;

class NKFADC500IBS : public TObject {
public:

	NKFADC500IBS();
	virtual ~NKFADC500IBS();
	int FADC500IBSopen(int sid, libusb_context *ctx);
	void FADC500IBSclose(int sid);
	unsigned long FADC500IBSread_BCOUNT(int sid);
	void FADC500IBSread_DATA(int sid, double bcount, unsigned char *data);

	ClassDef(NKFADC500IBS, 0) // NKFADC500IBS wrapper class for root
};

#endif
