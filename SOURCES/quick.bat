cd mos5src
\bc45\bin\make -f kernel.mak  
\bc45\bin\make -f makeutil.mak
\bc45\bin\make -f maketerm.mak
cd ..
                         
cd export
\bc45\bin\make -f export.mak
cd ..

cd import
\bc45\bin\make -f import.mak
cd ..

cd cutils
\bc45\bin\make -f hdsetup.mak
\bc45\bin\make -f install.mak
cd ..

cd mos5src
\bc45\bin\make -f discs.mak  
