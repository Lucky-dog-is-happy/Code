module Inhibit(X, Y, Z):
  input X, Y;
  output Z;

  assign Z = X & ~Y;
endmodule
