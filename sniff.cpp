/*
 * File: sniff.cpp 
 * Author: Zhang Xijin(mfs6174)
 * Email: mfs6174@gmail.com
 *
 * Copyright (C) 2011 Zhang Xijin(mfs6174)
 *
 * This file is part of XDnetmon.
 *
 * XDnetmon is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * XDnetmon is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with XDnetmon.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "include.h"
#include "h.h"

#define NODE 100000 //最大可能出现的节点数
#define CH 63 //分支数

tcphdr *dangtcp;
char *fuai;
bool yichuli;

int cc,c;//cc是统计使用了多少个节点
int zh[NODE][CH];//自动机机体
int shu[NODE];//相应节点的数据域
int fail[NODE];//失败指针，貌似是指向［彻底］失败的位置
int sn[300];//每个字符的代号，无效字符是0
int q[NODE];//队列
char pat[1000][1000];


void init() //每次都要先执行
{
  int i=0;
  char ch;
  for (ch='a';ch<='z';ch++)
  {
    i++;
    sn[ch]=i;
  }
  for (ch='A';ch<='Z';ch++)
  {
    i++;
    sn[ch]=i;
  }
  for (ch='0';ch<='9';ch++)
  {
    i++;
    sn[ch]=i;
  }
  ifstream inf("pat.txt");
  i=1;
  while (inf>>
  fail[0]=0;
  memset(zh[0],0,sizeof(zh[0]));
  cc=0;
}

void ins(char *s, int d) //建立trie
{
  int p=0;
  for(;*s;s++)
  {
    int t=sn[*a];
    if(!zh[p][t])
    {
      cc++;
      memset(zh[cc],0,sizeof(zh[cc]));
      shu[cc] = 0;
      zh[p][t] =cc;
    }
    p =zh[p][t];
  }
  shu[p]=d;
}

void acinit()//自动机初始化，执行完以后zh里就是goto或fail的位置
{
  int *s=q,*e=q,i;
  for (i=0;i<=CH;i++) //先把紧邻root的fail设成0
    if (zh[0][i])
    {
      fail[zh[0][i]]=0;
      *e++=zh[0][i];
    }
  while (s!=e)
  {
    int p=*s++;
    for (i=0;i<=CH;i++)
    {
      if (zh[p][i])//如果goto存在
      {
        int v=zh[p][i];
        *e++=v;
        fail[v]=zh[fail[p]][i];//fail直接设成彻底fail后应该转移的位置（最长后缀位置）
      }
      else
        zh[p][i]=zh[fail[p]][i];//goto不存在，转移到fail位置
    }
  }
}

void com(char *s) //查找每个模式串出现的次数
{
  int p=0;
  for (;*s;s++)
  {
    p=zh[p][sn[*s]];//转移
    int t=p;
    while (t)//跟随fail找符合的模式
    {
      if (shu[t])
      {
      }
      t=fail[t];
    }
  }
}

#define TH_OFF(th) (((th)->th_offx2 & 0xf0) >> 4)

void dosnif(u_char *bao,bpf_u_int32 ip,u_char xieyi)
{
  if (xieyi!=6)
  {
    return;
  }
  dangtcp=(struct tcphdr *)(bao);
  unsigned hl=TH_OFF(dangtcp)*4;
  if (hl<20)
    return;
  fuzai=(u_char *)(bao+hl);
  com(fuzai);
}


