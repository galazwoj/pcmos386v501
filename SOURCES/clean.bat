cd mos5src
\bc45\bin\make -f kernel.mak   clean
\bc45\bin\make -f makeutil.mak clean
\bc45\bin\make -f maketerm.mak clean
cd ..

cd ulib
\bc45\bin\make -f ulib.mak     clean
cd ..
                         
cd export
\bc45\bin\make -f export.mak   clean
cd ..

cd import
\bc45\bin\make -f import.mak   clean
cd ..

cd cutils
\bc45\bin\make -f hdsetup.mak  clean
\bc45\bin\make -f install.mak  clean
cd ..

cd acu
\bc45\bin\make 	clean
cd ..

cd mos5src
\bc45\bin\make -f discs.mak    clean
