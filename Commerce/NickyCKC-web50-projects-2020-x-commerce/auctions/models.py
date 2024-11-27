from django.contrib.auth.models import AbstractUser
from django.db import models


class User(AbstractUser):
    pass


class Category(models.Model):
    category_name = models.CharField(max_length=50)

    def __str__(self):
        return self.category_name


class Bid(models.Model):
    bid = models.DecimalField(default=0, max_digits=12, decimal_places=2)
    user = models.ForeignKey(User, blank=True, null=True, on_delete=models.CASCADE, related_name="user_bid")


class Listing(models.Model):
    title = models.CharField(max_length=50)
    description = models.CharField(max_length=500)
    price = models.ForeignKey(Bid, on_delete=models.CASCADE, blank=True, null=True, related_name="bid_price")
    image_url = models.CharField(max_length=1000)
    category = models.ForeignKey(Category, on_delete=models.CASCADE, blank=True, null=True, related_name="category")
    active = models.BooleanField(default=True)
    owner = models.ForeignKey(User, on_delete=models.CASCADE, blank=True, null=True, related_name="user")
    watchlist = models.ManyToManyField(User, blank=True, null=True, related_name="listing_watchlist")

    def __str__(self):
        return self.title


class Comment(models.Model):
    author = models.ForeignKey(User, on_delete=models.CASCADE, blank=True, null=True, related_name="user_comment")
    listing = models.ForeignKey(Listing, on_delete=models.CASCADE, blank=True, null=True, related_name="listing_comment")
    message = models.CharField(max_length=100)

    def __str__(self):
        return f"{self.author} comment on {self.listing}"