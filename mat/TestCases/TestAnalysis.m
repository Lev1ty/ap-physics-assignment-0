warning off;
flags=[];
error_indices=[];
parfor i=1:1000
    a=[]; b=[];
    [a,b]=check_equality(strcat('TestCaseIn',int2str(i),'.txt'),...
    strcat('TestCaseOut',int2str(i),'.txt'));
    c=isequal(round(a,3),round(b,3));
    flags=[flags c];
    if c==0
        error_indices=[error_indices i];
        disp(a);
        disp(b);
    end
end
function [mat_fit, out] = check_equality(inFile, outFile)
    in=transpose(importdata(inFile));
    out=transpose(importdata(outFile));
    num_points=in(1);
    deg=in(length(in));
    x=[]; y=[];
    for i=2:2:2*num_points+1
        x=[x in(i)];
        y=[y in(i+1)];
    end
    mat_fit=polyfit(x,y,deg);
end