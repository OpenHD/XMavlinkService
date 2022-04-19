# bin/bash

python3 mavlink/pymavlink/tools/mavgen.py --lang=C --wire-protocol=2.0 --output=c_library_v2_openhd mavlink/message_definitions/v1.0/openhd.xml