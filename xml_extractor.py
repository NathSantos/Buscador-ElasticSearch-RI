from xml.dom import minidom
import os

position_start_id = 6 

def id_converter(id):
    id = id[position_start_id:]
    return id

def text_converter(text):
    text = text.replace("\"", " ")
    text = text.replace("\n", " ")
    return text

#put here the path for regis-collection-master
path_to_data = "/home/matheus/Documents/A_COMPUTACAO/ri/elastic_project/xml_data_test/"

files_names = os.listdir(path_to_data)

for name_xml_file in files_names:
    file_path = path_to_data + name_xml_file
    # parse an xml file by name
    file = minidom.parse(file_path)

    #use getElementsByTagName() to get tag
    document = file.getElementsByTagName('field')

    id = id_converter(document[0].firstChild.data)
    filename = document[1].firstChild.data
    text = text_converter(document[3].firstChild.data)
    print("id:   " + id)
    print("name: " + filename)
    print("text: " + text)
    
    
    #DELETE THIS WHEN RUN FOR ALL FILES
    #name txt file for load the 
    txt_file = name_xml_file[position_start_id:len(name_xml_file)-3] + "txt"
    with open(txt_file, 'w') as f:
        f.write("id:         " + id + '\n')
        f.write("filename:   " + filename + '\n')
        f.write("text:       " + text + '\n')

