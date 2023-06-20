f [ $# -ne 2 ]
then
      echo "Usage: $0 source_file destination_file"
          exit 1
          fi

          if [ -e $2 ]
          then
                filename=$(basename $2)
                    extension="${filename##*.}"
                        filename="${filename%.*}"
                            counter=1
                                while [ -e "${filename}_${counter}.${extension}" ]
                                      do
                                                ((counter++))
                                                    done
                                                        cp "$1" "${filename}_${counter}.${extension}"
                                                      else
                                                            cp "$1" "$2"
          fi

