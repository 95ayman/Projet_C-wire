#!/usr/bin/bash

help() {
    echo "How to use the script"
    echo "$0 <data_file_path> <station_type> <consumer_type> [-h]"
    echo " example of utilisation:  ./c-wire.sh  data_file_path hva comp "
    echo "  <data_file_path>        Path to the data file . "
    echo "  <station_type>          hvb (high-voltage B), hva (high-voltage Q) or lv (low-voltage) "
    echo "  <consumer_type>         comp (company), indiv (individual), all (all) "
    echo "  -h                      show this help"
    echo ""
    echo "ATTENTION:The following combinations are forbidden because only company are connected"
    echo "  - hvb/all, hva/all, hvb/indiv, hva/indiv"
    echo ""

}
compile_function() {
     exec="exec"  
     makefile="Makefile"
    arg_station="$1"


    if [[ ! -f "$makefile" ]]; then
        echo "Makefile doesnt exist." 
        exit 1
    fi

    make


    if [[ ! -f "$exec" ]]; then
        echo " '$exec' did not work" 
        exit 1
    fi
    
    ./$exec "$arg_station"  # arg for the c part
}

Check_File() {
     data_File="$1"
    if [[ ! -f "$data_File" ]]; then
        echo "The $data_File File is not found." 
        help
        exit 1
    fi
}
     Check_arg() {
      station_type="$2"
      consumer_type="$3"
      if [[ "$station_type" != "hvb" && "$station_type" != "hva" && "$station_type" != "lv" ]]; then
        echo "This station type doesnt exist."
        help
        exit 1
    fi

   if [[ "$consumer_type" != "comp" && "$consumer_type" != "indiv" && "$consumer_type" != "all" ]]; then
        echo "This consumer doesnt exist."
        help
        exit 1
    fi


}
   Check_forbidden_arg() {
      station_type="$2"
     consumer_type="$3"

   if { [[ "$station_type" == "hvb" || "$station_type" == "hva" ]] && [[ "$consumer_type" == "all" || "$consumer_type" == "indiv" ]]; }; then
        echo "$station_type and $consumer_type does not exist." 
        help
        exit 1
    fi
}


Check_Tmp() {
    if [[ -d "tmp" ]]; then
        echo "tmp  already exists. "
        rm -rf tmp/* 
    else
        mkdir tmp
    fi
   
}

Check_Graphs() {
    if [[ -d "graphs" ]]; then
        echo "graphs  already exists."
    else
        mkdir graphs
    fi
}



filter_tmp_data() {
    local data_file="$1"
    local station_type="$2"
    local consumer_type="$3"
    local central_id="$4"
    local output_file="tmp/tmp.dat"
    local station_index consumer_index no_consumer

    determine_indices() {
        case "$1" in
            hvb) echo 2 ;;
            hva) echo 3 ;;
            lv) echo 4 ;;
        esac
    }

    station_index=$(determine_indices "$station_type")

    case "$consumer_type" in
        comp) consumer_index=5 ;;
        indiv) consumer_index=6 ;;
        all) consumer_index="all" ;;
    esac

    if [[ "$consumer_index" == 5 ]]; then
        no_consumer=6
    else
        no_consumer=5
    fi

    process_data() {
        awk -F';' \
            -v station_idx="$1" \
            -v consumer_idx="$2" \
            -v central_id="$3" \
            -v no_consumer_idx="$4" \
            'BEGIN { OFS = ";" } \
            NR == 1 { next } \
            {
                station_value = $station_idx;
                consumer_value = (consumer_idx == "all" ? "valid" : $consumer_idx);
                no_consumer_value = $no_consumer_idx;

                if ((station_value != "-" && no_consumer_value == "-") || (station_value != "-" && consumer_value != "-")) {
                    if (central_id == "all" || central_id == $1) {
                        print >> "tmp/tmp.dat";
                    }
                }
            }' "$data_file"
    }

    process_data "$station_index" "$consumer_index" "$central_id" "$no_consumer"



    echo "data saved in $output_file for the c part..."

}


main() {
     data_File="$1"
     station_type="$2"
     consumer_type="$3"
     central_id="${4:-all}"  

    if [[ "$*" == "h" ]]; then
        help
        exit 0
    fi

    if [[ $# -lt 3 ]]; then
        echo "You need to put 3 parameters"
        help
        exit 1
    fi

    

    Check_File "$data_File" "$station_type" "$consumer_type"
    
    Check_arg "$data_File" "$station_type" "$consumer_type"

    Check_forbidden_arg "$data_File" "$station_type" "$consumer_type"
    
    Check_Tmp

    Check_Graphs

    filter_tmp_data "$data_File" "$station_type" "$consumer_type" "$central_id"

    
    compile_function "$station_type"

    make clean 

    echo " The data File is ready in data.csv "
    
}

main "$@"
