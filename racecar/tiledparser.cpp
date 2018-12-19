#include "tiledparser.h"
tmxtag::tmxtag()
{
}

tmxtag::tmxtag(string space)
{
	maxtags = 0;
	keysize = 0;
	string headline = space;
	for (int i = 0; i < headline.size(); i++) {
		if (headline[i] == '<') {
			for (int ii = i + 1; ii < headline.size(); ii++) {
				if (headline[ii] == ' ' || headline[ii] == '/') {
					keys[keysize] = "type";
					values[keysize] = headline.substr(i, ii - i);
					i = ii - 1;
					keysize += 1;
					break;
				}
			}
		}
		else if (headline[i] == ' ') {
			int mid;
			int end;
			for (int ii = i + 1; ii < headline.size(); ii++) {
				if (headline[ii] == '=') {
					mid = ii;
					break;
				}
			}
			for (int ii = mid + 2; ii < headline.size(); ii++) {
				if (headline[ii] == '"' || headline[ii] == '/' || headline[ii] == '>') {
					end = ii;
					break;
				}
			}
			keys[keysize] = headline.substr(i, mid - i);
			values[keysize] = headline.substr(mid + 1, end - mid+1);
			keysize += 1;
			i = end - 1;
		}
	}
	//clean keys and such
	for (int i = 0; i<keysize; i++) {

		while (keys[i][0] == ' ' || keys[i][0] == '<' || keys[i][0] == '"') {
			keys[i] = keys[i].substr(1, keys[i].size() - 1);
		}
		while (keys[i][keys[i].size() - 1] == ' ' || keys[i][keys[i].size() - 1] == '>' || keys[i][keys[i].size() - 1] == '"') {
			keys[i] = keys[i].substr(0, keys[i].size() - 1);
		}
		while (values[i][0] == ' ' || values[i][0] == '<' || values[i][0] == '"') {
			values[i] = values[i].substr(1, values[i].size() - 1);
		}
		while (values[i][values[i].size() - 1] == ' ' || values[i][values[i].size() - 1] == '>' || values[i][values[i].size() - 1] == '"' || values[i][values[i].size() - 1] == '/') {
			values[i] = values[i].substr(0, values[i].size() - 1);
		}

	}
}

tmxtag::tmxtag(string space[], int initial, int final)
{
	maxtags = 0;
	keysize = 0;
	string headline = space[initial];
	for (int i = 0; i < headline.size(); i++) {

		if (headline[i] == '<') {
			for (int ii = i + 1; ii < headline.size(); ii++) {
				if (headline[ii] == ' ' || headline[ii] == '/'|| headline[ii] == '>') {
					keys[keysize] = "type";
					values[keysize] = headline.substr(i, ii - i);
					i = ii - 1;
					keysize += 1;
					break;
				}
			}
		}
		else if (headline[i] == ' ') {
			int mid=0;
			int end;
			for (int ii = i; ii < headline.size(); ii++) {
				if (headline[ii] == '=') {
					mid = ii;
					break;
				}
			}
			for (int ii = mid + 1; ii < headline.size(); ii++) {
				if (headline[ii] == ' ' || headline[ii] == '/' || headline[ii] == '>') {
					end = ii;
					break;
				}
			}
			keys[keysize] = headline.substr(i, mid - i);
			values[keysize] = headline.substr(mid + 1, end - mid);
			keysize += 1;
			i = end - 1;
		}
	}
	//clean keys and such
	for (int i = 0; i<keysize; i++) {

		while (keys[i][0] == ' ' || keys[i][0] == '<' || keys[i][0] == '"') {
			keys[i] = keys[i].substr(1, keys[i].size() - 1);
		}
		while (keys[i][keys[i].size() - 1] == ' ' || keys[i][keys[i].size() - 1] == '>' || keys[i][keys[i].size() - 1] == '"') {
			keys[i] = keys[i].substr(0, keys[i].size() - 1);
		}
		while (values[i][0] == ' ' || values[i][0] == '<' || values[i][0] == '"') {
			values[i] = values[i].substr(1, values[i].size() - 1);
		}
		while (values[i][values[i].size() - 1] == ' ' || values[i][values[i].size() - 1] == '>' || values[i][values[i].size() - 1] == '"') {
			values[i] = values[i].substr(0, values[i].size() - 1);
		}

	}


	tagCount = 0;
 	for (int i = initial+1; i < final; i++) {
		if (tagCount >= maxtags) {
			maxtags = maxtags + 10;
			tmxtag * *temp = new tmxtag*[maxtags];
			for (int i = 0; i < tagCount; i++) {
				temp[i] = tags[i];
			}
			delete tags;
			tags = temp;
		}
		if (space[i][0] == '<') {//find the start of the tag tocases
			if (space[i].find('/') != string::npos) {//single line tag
				tags[tagCount] = new tmxtag(space[i]);
				tagCount += 1;
			}
			else {
				//get tag type;
				int start;
				int end;
				for (start = 0; start < space[i].size(); start++) {
					if (space[i][start] == '<') {
						break;
					}
				}
				for (end = start; end < space[i].size(); end++) {
					if (space[i][end] == '>' || space[i][end] == ' ') {
						break;
					}
				}
				string tagtype = space[i].substr(start + 1, end - start - 1);
				tagtype = string("</") + tagtype + ">";
				for (int ii = i + 1; ii < final; ii++) {
					if (tagtype.compare(string(space[ii].c_str())) == 0) {
						tags[tagCount] = new tmxtag(space, i, ii);
						tagCount += 1;
						i = ii;
						break;
					}
				}
			}
		}
		else {
			data += space[i] + "\n";
		}
	}
}


tmxtag::tmxtag(string path, int differ)
{
	maxtags = 0;
	ifstream infile;
	infile.open(path.c_str());
	if (!infile) {
		throw 1;
		exit(1);
	}
	int filesize = 0;
	string file[400];
	string line;
	while (getline(infile, line)) {
		while (line[0] == ' ') {
			line = line.substr(1, line.size() - 1);
		}
		while ((line[line.size()] == ' ') | (line[line.size()] == '\n')) {
			line = line.substr(0, line.size() - 1);
		}
		file[filesize] = line;
		filesize += 1;
	}
	//line to space for head
	keysize = 0;
	string headline = file[1];
	for (int i = 0; i < headline.size(); i++) {

		if (headline[i] == '<') {
			for (int ii = i+1; ii < headline.size();ii++) {
				if (headline[ii] == ' ' || headline[ii] == '/') {
					keys[keysize] = "type";
					values[keysize] = headline.substr(i, ii-i);
					i = ii-1;
					keysize += 1;
					break;
				}
			}
		}
		else if (headline[i] == ' ') {
			int mid;
			int end;
			for (int ii = i+1; ii < headline.size(); ii++) {
				if (headline[ii] == '=') {
					mid = ii;
					break;
				}
			}
			for (int ii = mid+1; ii < headline.size(); ii++) {
				if (headline[ii] == ' ' || headline[ii] == '/' || headline[ii]=='>') {
					end = ii;
					break;
				}
			}
			keys[keysize] = headline.substr(i, mid-i);
			values[keysize] = headline.substr(mid+1,end-mid);
			keysize += 1;
			i = end-1;
		}
	}
	//clean keys and such
	for(int i=0;i<keysize;i++){

		while(keys[i][0]==' '|| keys[i][0] == '<' || keys[i][0] == '"'){
			keys[i] = keys[i].substr(1, keys[i].size()-1);
		}
		while (keys[i][keys[i].size() - 1] == ' ' || keys[i][keys[i].size() - 1] == '>' || keys[i][keys[i].size() - 1] == '"') {
			keys[i] = keys[i].substr(0, keys[i].size() - 1);
		}
		while (values[i][0] == ' ' || values[i][0] == '<' || values[i][0] == '"') {
			values[i] = values[i].substr(1, values[i].size() - 1);
		}
		while (values[i][values[i].size() - 1] == ' ' || values[i][values[i].size() - 1] == '>' || values[i][values[i].size() - 1] == '"') {
			values[i] = values[i].substr(0, values[i].size() - 1);
		}
	
	}


	tagCount = 0;
	for (int i = 2; i < filesize-1; i++) {
		

		if (tagCount >= maxtags) {
			maxtags = maxtags + 10;
			tmxtag * *temp =  new tmxtag*[maxtags];
			for (int i = 0; i < tagCount;i++) {
				temp[i] = tags[i];
			}
			delete tags;
			tags = temp;
		}




		if (file[i][0] == '<') {//find the start of the tag tocases
			
			if (file[i].find('/')!=string::npos) {//single line tag
				tags[tagCount] = new tmxtag(file[i]);
				tagCount += 1;
			}
			else {
				//get tag type;
				int start;
				int end;
				for (start = 0; start < file[i].size(); start++) {
					if (file[i][start] == '<') {
						break;
					}
				}
				for (end = start; end < file[i].size(); end++) {
					if (file[i][end] == '>'|| file[i][end] == ' ') {
						break;
					}
				}
				string tagtype = file[i].substr(start+1,end-start-1);
				tagtype = string("</") + tagtype + ">";
				for (int ii = i + 1; ii < filesize-1; ii++) {

					if (tagtype.compare(string(file[ii].c_str())) == 0) {
						tags[tagCount] = new tmxtag(file,i,ii);
						tagCount += 1;
						i = ii;
						break;
					}
				}
			}
		}
	}
	
}

string tmxtag::head()
{
	for (int i = 0; i < keysize; i++) {
		
	}
	
	return string();
}

void tmxtag::display(int indent)
{
	for (int i = 0; i < indent; i++) {
		
	}

	this->head();
	for (int i = 0; i < tagCount; i++) {
		tags[i]->display(indent + 1);
	}
}

string tmxtag::head(string key)
{
	for (int i = 0; i < keysize; i++) {
		if (key.compare(keys[i])==0) {
			return values[i];
		}
	}
	return "none";
}

int tmxtag::tagcount()
{
	return tagCount;
}

tmxtag tmxtag::get(int i)
{
	return *tags[i];
}

string tmxtag::getData()
{
	return data;
}

bool tmxtag::clear()
{
	for (int i = 0; i < tagCount; i++) {
		tags[i]->clear();
		delete tags[i];
	}
	delete tags;

	return false;
}
