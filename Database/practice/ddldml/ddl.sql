create table person(

    NID varchar2(15) constraint person_pk primary key,
    name varchar2(50) not null,
    bdate date default sysdate

);


create table person2(
     NID varchar2(15) ,
    name varchar2(50) not null,
    bdate date default sysdate,
    constraint person_pk2 primary key(NID)
);

create table person3(
    countryID char(3),
    personID varchar2(15),
    name varchar2(50) not null unique,
    bdate date default sysdate,
    constraint person_pk3 primary key(countryID, personID)
);

create table person_adress
(
    pid varchar2(15),
    addr_line1 varchar2(50),
    addr_line2 varchar2(50),
    city varchar2(50) not null,
    district varchar2(50) not null,
    constraint person_adress_fk foreign key (pid) references person(nid)
    on delete cascade
);

alter table person3 drop column bdate;
alter table person3 add bdate date;
