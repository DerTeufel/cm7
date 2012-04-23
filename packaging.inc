#!/bin/sh

release() {
## version= "$1"
#REL=${version}_$(date +%Y%m%d_%H_%M)
REL=${version}_$(date +%Y%m%d)

rm -r release/system 2> /dev/null
mkdir  -p release/system/bin || exit 1
mkdir  -p release/system/lib/modules || exit 1
mkdir  -p release/system/lib/hw || exit 1
mkdir  -p release/system/etc/init.d || exit 1
mkdir  -p release/system/etc/devil || exit 1
find . -name "*.ko" -exec cp {} release/system/lib/modules/ \; 2>/dev/null || exit 1

cd release && {
if [ "$light" = "BLN" ] 
then
        cp lights.aries.so.BLN system/lib/hw/lights.aries.so || exit 1
	cp updater-script.BLN META-INF/com/google/android/updater-script || exit 1
else
#	cp lights.aries.so system/lib/hw/|| exit 1
#	cp lights.goldfish.so system/lib/hw/|| exit 1
	cp updater-script.LED META-INF/com/google/android/updater-script || exit 1
fi

#if [ "$mem" = "cm" ]
#then
#	cp cm/* system/lib/ || exit 1
#else	
#	cp xl/* system/lib/ || exit 1
#fi	

#	cp S30datafix system/etc/init.d/ || exit 1
#	cp S98oc_value system/etc/init.d/ || exit 1
#	cp S99load_default system/etc/init.d/ || exit 1
#	cp S80profiles system/etc/init.d/ || exit 1
#	cp profile system/etc/devil/ || exit 1
#	cp bootspeed system/etc/devil/ || exit 1
#	cp live_oc_mode system/etc/devil/ || exit 1
#	cp vibrator system/etc/devil/ || exit 1

	mkdir -p system/bin
	zip -q -r "${REL}.zip" system data backup boot.img META-INF erase_image flash_image bml_over_mtd bml_over_mtd.sh || exit 1
	sha256sum ${REL}.zip > ${REL}.sha256sum

} || exit 1

echo ${REL}
rm system/lib/modules/* 
rm system/lib/hw/* 
rm system/etc/init.d/* 
rm system/bin/*
cd ..
return 0
}
