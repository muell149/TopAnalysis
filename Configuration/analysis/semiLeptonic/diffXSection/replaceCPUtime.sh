
if [ $# -ne 1 ]; then

    echo ""
    echo "Usage: ./replaceCPUTime.sh <bool p1> "
    echo ""
    echo "p1: - Create backup copy of script to be modified"
    echo "    - Allowed values: 0/1"

else

    for FILE in `ls naf_*/j_*.sh`; do
	
	if [ ${1} == 1 ]; then
	    echo "Copying ${FILE} to ${FILE}.backup"
	    cp ${FILE} ${FILE}.backup
	fi
	
	echo "Modifying ${FILE}"
	
# 	sed -i 's/h_cpu=12:00:00/h_cpu=48:00:00/' ${FILE}
# 	sed -i 's/s_cpu=11:55:00/s_cpu=47:55:00/' ${FILE}
# 	sed -i 's/s_rt=11:55:00/s_rt=47:55:00/'   ${FILE}

	sed -i 's/h_cpu=1:00:00/h_cpu=12:00:00/' ${FILE}
	sed -i 's/s_cpu=0:55:00/s_cpu=11:55:00/' ${FILE}
	sed -i 's/s_rt=0:55:00/s_rt=11:55:00/'   ${FILE}
	
    done

fi