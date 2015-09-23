drop database if exists sso;
create database sso;
use sso;
create table user(
	username varchar(16) primary key,
	pwd char(16)	
);
