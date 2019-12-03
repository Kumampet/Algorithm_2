#include <stdio.h>
#include <stdlib.h>

typedef struct node N;
typedef struct code C;

/* Data of Haffman tree */
struct node {
  N *parent;
  N *left;
  N *right;
  N *next;
  unsigned int freq;
  char chr;
};

/* Data of Haffman Code */
struct code {
  char chr;
  int value;
  char bit;
  C *next;
};

/* 指定されたchrを持つ節を探す関数 */
/* 見つかった場合はその節へのポインタ、
   見つからなかった場合はNULLを返却 */
N *searchNode(N *node, char chr){
  while(node != NULL){
    if(node->chr == chr){
      return node;
    }
    node = node->next;
  }
  return node;
}

/* 節を追加する関数 */
N *newNode(char chr){
  N *node;

  node = (N*)malloc(sizeof(N));
  if(node == NULL){
    return NULL;
  }

  /* 親や子を指すポインタはNULLで初期化 */
  node->parent = NULL;
  node->left = NULL;
  node->right = NULL;
  node->next = NULL;

  node->freq = 1;
  node->chr = chr;

  return node;
}

/* 文字の出現関数をカウントし、
   その出現関数を持つ節を生成 */
N *makeNodes(char *filename){
  N *head;
  N *tail;
  N *add;
  N *search;
  char chr;
  FILE *fp;

  head = NULL;
  tail = NULL;

  /* ファイルをオープン */
  fp = fopen(filename, "r");
  if(fp == NULL){
    printf("%s open error\n", filename);
    return NULL;
  }


  /* 全文字読み終わるまで１文字ずつ読み取り */
  while((chr = fgetc(fp)) != EOF){
    /* その文字に対応する節を探索 */
    search = searchNode(head, chr);
    if(search == NULL){
      /* 節がない場合は新しく節を追加 */
      add = newNode(chr);
      if(add == NULL){
        printf("node malloc error\n");
        fclose(fp);
        return NULL;
      }

      /* 最初の節の場合はheadとtailにその節を指させる */
      if(head == NULL){
        head = add;
        tail = add;
      } else {
        /* すでに節がある場合は終端に節を追加 */
        tail->next = add;
        tail = add;
      }
    } else {
      /* その文字に対応する節がある場合は出現関数をカウントアップ */
      search->freq++;
    }
  }

  fclose(fp);

  return head;
}

/* 親のいない節の中から一番出現関数が少ない節と、
   二番目に出現回数が少ない節を探索する関数 */
/* 一番出現回数が少ない節はleftに
   二番目に出現回数が少ない節はrightに指させる */
void getChild(N **left, N **right, N *head){
  /* 出現回数の最小値を格納する変数 */
  unsigned int first = 999999;

  /* 出現回数の二番目に小さい値を格納する変数 */
  unsigned int second = 999999;

  *left = NULL;
  *right = NULL;

  /* リストの先頭から探索 */
  while(head != NULL){
    if(head->parent == NULL){
      /* 出現回数が一番少ないかどうかを判断 */
      if(first > head->freq && second > head->freq){
        first = head->freq;
        *right = *left;
        *left = head;
      /* 出現回数が二番目に少ないかどうかを判断 */
      } else if(second > head->freq){
        second = head->freq;
        *right = head;
      }
    }
    /* headを次の節へ進ませる */
    head = head->next;
  }
}

/* ハフマン木を作成する関数 */
void makeHuffmanTree(NODE *head){
  NODE *left = NULL;
  NODE *right = NULL;
  NODE *tail = NULL;
  NODE *add = NULL;

  if(head == NULL){
    printf("head is NULL\n");
    return ;
  }

  /* リストの終端までtailを移動 */
  tail = head;
  while(tail->next != NULL){
    tail = tail->next;
  }

  /* 出現回数の少ない二つの節を取得 */
  getChild(&left, &right, head);

  /* 親のいない節が２つ未満になるまでループ */
  while(left != NULL & right != NULL){
    /* 新しいノードを追加 */
    /* 文字情報は'\0'とする */
    add = newNode('\0');
    if(add == NULL){
      printf("malloc error\n");
      return ;
    }

    /* 追加した節はleftとrightの親となるようにパラメータ設定 */
    left->parent = add;
    right->parent = add;
    add->left = left;
    add->right = right;
    add->freq = left->freq + right->freq;

    /* 追加した節をリストの終端に登録 */
    tail->next = add;
    tail = add;

    /* 出現回数の少ない二つの節を取得 */
    getChild(&left, &right, head);
  }
}

/* 文字にハフマン符号を割り当て、
   その情報をCODE構造体に格納する関数 */
CODE *makeHuffmanCode(NODE *node){
  NODE *child = NULL;
  NODE *parent = NULL;
  CODE *code = NULL;
  CODE *top = NULL;
  CODE *add = NULL;

  /* 符号（ビット列） */
  int value;

  /* 符号のビット数 */
  int bit;

  /* 葉全てに符号を割り当てたらループ終了 */
  /* 葉以外の節の文字は'\0' */
  while(node != NULL && node->chr != '\0'){
    /* 符号とそのビット数を0に初期化 */
    value = 0;
    bit = 0;

    /* CODE構造体を追加 */
    add = (CODE*)malloc(sizeof(CODE));
    if(add == NULL){
      printf("malloc error\n");
      return NULL;
    }

    /* 追加したCODE構造体の文字を設定 */
    add->chr = node->chr;

    /* childは今注目している節へのポインタ */
    child = node;

    /* parentは今注目している節の親へのポインタ */
    parent = node->parent;

    /* 葉から根まで親を遡っていく */
    /* 根の節はparentがNULL */
    while(parent != NULL){
      /* 親から見て今注目している節が左の子の場合 */
      if(parent->left == child){
        /* ビット列（value）の一番左へビット0を追加 */
        value = value + (0 << bit);
      /* 親から見て今注目している節が右の子の場合 */
      } else if(parent->right == child){
        /* ビット列（value）の一番左へビット1を追加 */
        value = value + (1 << bit);
      }
      /* ビット列のビット数を1増やす */
      bit++;

      /* 今注目している節の親を、新たな注目節に更新 */
      child = parent;

      /* 親も親の親に更新 */
      parent = parent->parent;
    }

    /* 符号を求め終わったので、
       追加したCODEに符号そのものとそのビット数を設定 */
    add->value = value;
    add->bit = bit;

    /* CODE構造体がまだ一つもない場合 */
    if(code == NULL){
      code = add;
      top = code;

    /* CODE構造体がすでにある場合は最後尾に追加 */
    } else {
      code->next = add;
      code = code->next;
    }

    /* 次の節に対して符号を算出 */
    node = node->next;
  }

  return top;
}

/* nodeが先頭を指すNODE構造体のリストを全削除する関数 */
void freeNode(NODE *node){
  NODE *next;

  while(node != NULL){
    next = node->next;
    free(node);
    node = next;
  }
}

/* codeが先頭を指すCODE構造体のリストを全削除する関数 */
void freeCode(CODE *code){
  CODE *next;

  while(code != NULL){
    next = code->next;
    free(code);
    code = next;
  }
}

/* 引数chrの文字をchrメンバに持つCODE構造体を探索する関数 */
CODE *searchCode(CODE *head, char chr){
  while(head != NULL){
    if(head->chr == chr){
      return head;
    }
    head = head->next;
  }
  return NULL;
}

/* 符号化を行なってファイルに書き出しする関数 */
void encodeFile(char *outname, char *inname, CODE *head){
  FILE *fi;
  FILE *fo;
  CODE *code;
  unsigned char byte;
  char emptyBits;

  unsigned int textlength;
  int mask;
  char oneBit;
  unsigned int headerSize;
  char chr;
  int i;

  /* 終端を表す文字を格納 */
  char terminal = '\0';

  /* 入力ファイルを開く */
  fi = fopen(inname, "r");
  if(fi == NULL){
    printf("%s open error\n", inname);
    return ;
  }

  /* 入力ファイルの文字数をカウント */
  textlength = 0;
  while((chr = fgetc(fi)) != EOF){
    textlength++;
  }

  /* 入力ファイルを一旦クローズ */
  fclose(fi);

  /* 出力ファイルを開く */
  fo = fopen(outname, "wb");
  if(fo == NULL){
    printf("%s open error\n", outname);
    fclose(fi);
    return ;
  }

  /* ヘッダーを書き込む */
  headerSize = 0;
  code = head;

  /* CODE構造体のリストの先頭から終端まで、
     文字の符号化情報をヘッダーとして書きだす */
  while(code != NULL){
    /* まず文字を書き込む */
    fwrite(&(code->chr), sizeof(code->chr), 1, fo);

    /* 符号化文字のビット数を書き込む */
    fwrite(&(code->bit), sizeof(code->bit), 1, fo);

    /* この文字のエンコード結果を書き込む */
    fwrite(&(code->value), sizeof(code->value), 1, fo);

    headerSize += sizeof(code->chr) + sizeof(code->bit) + sizeof(code->value);

    /* 次の文字の符号化情報書き出しに移る */
    code = code->next;
  }

  /* ヘッダーの終端として'\0'と文字数を書き出す */
  fwrite(&terminal, 1, 1, fo);
  fwrite(&textlength, sizeof(textlength), 1, fo);

  headerSize += 1 + sizeof(textlength);
  printf("Header Size is %d bytes\n", headerSize);

  /* 入力ファイルを開く */
  fi = fopen(inname, "r");
  if(fi == NULL){
    printf("%s open error\n", inname);
    return ;
  }

  /* バイトデータを0で初期化 */
  byte = 0;

  /* バイトデータの空きビット数を8に設定 */
  emptyBits = 8;

  /* ファイルから１文字ずつ読み込み */
  while((chr = fgetc(fi)) != EOF){

    /* 読み込んだ文字に対応するCODE構造体を取得 */
    code = searchCode(head, chr);

    /* 符号の最上位ビットからバイトデータへ詰め合わせ */
    for(i = code->bit - 1; i >= 0; i--){

      /* iビット目が1でそれ以外が0のビット列を作成 */
      mask = 1 << i;

      /* iビット目以外を0にしたのちiビット分右シフト */
      oneBit = (code->value & mask) >> i;

      /* バイトデータの空きビット数 - 1分左シフトして足し合わせ */
      byte += oneBit << (emptyBits - 1);

      /* 空いているビット数を1減らす */
      emptyBits--;

      /* 空いているビットが0になったらファイルへ書き出し */
      if(emptyBits == 0){
        fwrite(&byte, 1, 1, fo);

        /* ファイルに書き出したので空きビット数を8、
           byteを0で初期化 */
        emptyBits = 8;
        byte = 0;
      }
    }
  }

  /* 1バイト分つまらなかった分を最後にファイルへ書き出し */
  if(emptyBits < 8){
    fwrite(&byte, 1, 1, fo);
  }

  /* 開いていたファイルをクローズ */
  fclose(fi);
  fclose(fo);
}

int main(int argc, char* argv[]){

  NODE *nodes;
  CODE *codes;
  char outname[256];

  if(argc != 2){
    printf("引数に入力ファイル名を指定してください\n");
    return -1;
  }

  nodes = makeNodes(argv[1]);

  makeHuffmanTree(nodes);

  codes = makeHuffmanCode(nodes);

  freeNode(nodes);

  sprintf(outname, "huffman.enc");

  encodeFile(outname, argv[1], codes);

  return 0;
}