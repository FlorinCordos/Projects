 abstract public class Car {

    private String producer;
    private String model;
    private int year;
    private double price;
    private int kilometres;

    public Car(String producer, String model, int year, double price, int kilometres) {
        this.producer = producer;
        this.model = model;
        this.year = year;
        this.price = price;
        this.kilometres = kilometres;
    }
  //abstract public void carData();
    public abstract String getFuelType();
    public abstract void getCarDetails();

     public void setProducer(String producer) {
         this.producer = producer;
     }

     public void setModel(String model) {
         this.model = model;
     }

     public void setYear(int year) {
         this.year = year;
     }

     public void setPrice(double price) {
         this.price = price;
     }

     public void setKilometres(int kilometres) {
         this.kilometres = kilometres;
     }

     public String getProducer() {
         return producer;
     }

     public String getModel() {
         return model;
     }

     public int getYear() {
         return year;
     }

     public double getPrice() {
         return price;
     }

     public int getKilometres() {
         return kilometres;
     }
 }
