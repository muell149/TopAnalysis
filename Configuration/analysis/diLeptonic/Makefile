ROOTLIBS=`root-config --libs`
ROOTFLAGS=`root-config --cflags`

INCS= ${ROOTFLAGS} ${ROOTLIBS} -lMinuit -lMLP -lTreePlayer

COMPFLAGS=-g

all: mergemc.exe

mergemc.exe : merge_mc.C
	g++ $(COMPFLAGS) -o mergemc.exe merge_mc.C ${INCS}

clean:
	rm mergemc.exe