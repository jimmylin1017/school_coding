#!/usr/bin/awk -f
NR==1{OFS="   "
	for(i=2;i<=NF;i++)
		L[i]=$i
	$1=$1
	OFS="  "
}
NR!=1{for(i=1;i<=NF;i++)
	if($i in S)
		$i=S[$i]
	else
	{	S[$i]=L[i](NR-1)/2
		$i=$i" "
	}
}
1